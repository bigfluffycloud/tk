#include <core/elf.h>
#include <string.h>
#include <stdlib.h>
bool elf_check_file(Elf32_Ehdr *hdr) {
	if (!hdr)
	   return false;
	if (hdr->e_ident[EI_MAG0] != ELFMAG0) {
	   cons_write("ELF Header EI_MAG0 incorrect.\n");
	   return false;
	}

	if (hdr->e_ident[EI_MAG1] != ELFMAG1) {
           cons_write("ELF Header EI_MAG1 incorrect.\n");
           return false;
	}

	if (hdr->e_ident[EI_MAG2] != ELFMAG2) {
           cons_write("ELF Header EI_MAG2 incorrect.\n");
           return false;
	}

	if (hdr->e_ident[EI_MAG3] != ELFMAG3) {
	   cons_write("ELF Header EI_MAG3 incorrect.\n");
	   return false;
	}

	return true;
}

bool elf_check_supported(Elf32_Ehdr *hdr) {
     if (!elf_check_file(hdr)) {
        cons_write("Invalid ELF File.\n");
        return false;
     }

     if (hdr->e_ident[EI_CLASS] != ELFCLASS32) {
        cons_write("Unsupported ELF File Class.\n");
        return false;
     }

     if (hdr->e_ident[EI_DATA] != ELFDATA2LSB) {
	cons_write("Unsupported ELF File byte order.\n");
	return false;
     }

     if (hdr->e_machine != EM_386) {
        cons_write("Unsupported ELF File target.\n");
        return false;
     }

     if (hdr->e_ident[EI_VERSION] != EV_CURRENT) {
	cons_write("Unsupported ELF File version.\n");
	return false;
     }

     if (hdr->e_type != ET_REL && hdr->e_type != ET_EXEC) {
	cons_write("Unsupported ELF File type.\n");
	return false;
     }

     return true;
}
 
void *elf_load_file(void *file) {
     Elf32_Ehdr *hdr = (Elf32_Ehdr *)file;

     if (!elf_check_supported(hdr)) {
	cons_write("ELF File cannot be loaded.\n");
	return;
     }

     switch (hdr->e_type) {
	case ET_EXEC:
	   // TODO : Implement
	   return NULL;
	case ET_REL:
           return elf_load_rel(hdr);
     }
     return NULL;
}

static int elf_get_symval(Elf32_Ehdr *hdr, int table, uint idx) {
	if(table == SHN_UNDEF || idx == SHN_UNDEF) return 0;
	Elf32_Shdr *symtab = elf_section(hdr, table);
 
	uint32_t symtab_entries = symtab->sh_size / symtab->sh_entsize;
	if(idx >= symtab_entries) {
		cons_write("Symbol Index out of Range (%d:%u).\n", table, idx);
		return ELF_RELOC_ERR;
	}
 
	int symaddr = (int)hdr + symtab->sh_offset;
	Elf32_Sym *symbol = &((Elf32_Sym *)symaddr)[idx];
	if(symbol->st_shndx == SHN_UNDEF) {
		// External symbol, lookup value
		Elf32_Shdr *strtab = elf_section(hdr, symtab->sh_link);
		const char *name = (const char *)hdr + strtab->sh_offset + symbol->st_name;
 
		extern void *elf_lookup_symbol(const char *name);
		void *target = elf_lookup_symbol(name);
 
		if(target == NULL) {
			// Extern symbol not found
			if(ELF32_ST_BIND(symbol->st_info) & STB_WEAK) {
				// Weak symbol initialized as 0
				return 0;
			} else {
				cons_write("Undefined External Symbol : %s.\n", name);
				return ELF_RELOC_ERR;
			}
		} else {
			return (int)target;
		}
	} else if(symbol->st_shndx == SHN_ABS) {
		// Absolute symbol
		return symbol->st_value;
	} else {
		// Internally defined symbol
		Elf32_Shdr *target = elf_section(hdr, symbol->st_shndx);
		return (int)hdr + symbol->st_value + target->sh_offset;
	}
}
static int elf_load_stage1(Elf32_Ehdr *hdr) {
	Elf32_Shdr *shdr = elf_sheader(hdr);
 
	unsigned int i;
	// Iterate over section headers
	for(i = 0; i < hdr->e_shnum; i++) {
		Elf32_Shdr *section = &shdr[i];
 
		// If the section isn't present in the file
		if(section->sh_type == SHT_NOBITS) {
			// Skip if it the section is empty
			if(!section->sh_size) continue;
			// If the section should appear in memory
			if(section->sh_flags & SHF_ALLOC) {
				// Allocate and zero some memory
				void *mem = malloc(section->sh_size);
				memset(mem, 0, section->sh_size);
 
				// Assign the memory offset to the section offset
				section->sh_offset = (int)mem - (int)hdr;
				cons_write("DEBUG: Allocated memory for a section (%ld).\n", section->sh_size);
			}
		}
	}
	return 0;
}
 
static int elf_load_stage2(Elf32_Ehdr *hdr) {
	Elf32_Shdr *shdr = elf_sheader(hdr);
 
	unsigned int i, idx;
	// Iterate over section headers
	for(i = 0; i < hdr->e_shnum; i++) {
		Elf32_Shdr *section = &shdr[i];
 
		// If this is a relocation section
		if(section->sh_type == SHT_REL) {
			// Process each entry in the table
			for(idx = 0; idx < section->sh_size / section->sh_entsize; idx++) {
				Elf32_Rel *reltab = &((Elf32_Rel *)((int)hdr + section->sh_offset))[idx];
				int result = elf_do_reloc(hdr, reltab, section);
				// On error, display a message and return
				if(result == ELF_RELOC_ERR) {
					cons_write("Failed to relocate symbol.\n");
					return ELF_RELOC_ERR;
				}
			}
		}
	}
	return 0;
}
# define DO_386_32(S, A)	((S) + (A))
# define DO_386_PC32(S, A, P)	((S) + (A) - (P))
 
static int elf_do_reloc(Elf32_Ehdr *hdr, Elf32_Rel *rel, Elf32_Shdr *reltab) {
	Elf32_Shdr *target = elf_section(hdr, reltab->sh_info);
 
	int addr = (int)hdr + target->sh_offset;
	int *ref = (int *)(addr + rel->r_offset);
		// Symbol value
	int symval = 0;
	if(ELF32_R_SYM(rel->r_info) != SHN_UNDEF) {
		symval = elf_get_symval(hdr, reltab->sh_link, ELF32_R_SYM(rel->r_info));
		if(symval == ELF_RELOC_ERR) return ELF_RELOC_ERR;
	}
		// Relocate based on type
	switch(ELF32_R_TYPE(rel->r_info)) {
		case R_386_NONE:
			// No relocation
			break;
		case R_386_32:
			// Symbol + Offset
			*ref = DO_386_32(symval, *ref);
			break;
		case R_386_PC32:
			// Symbol + Offset - Section Offset
			*ref = DO_386_PC32(symval, *ref, (int)ref);
			break;
		default:
			// Relocation type not supported, display error and return
			cons_write("Unsupported Relocation Type (%d).\n", ELF32_R_TYPE(rel->r_info));
			return ELF_RELOC_ERR;
	}
	return symval;
}

