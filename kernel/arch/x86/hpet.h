#if	!defined(__machine_hpet_h)
#define	__machine_hpet_h
#include <config.h>
#include <sys/stddef.h>
#include <sys/types.h>

#if	defined(CPU_X86)
typedef uint32_t addr_t;
#endif

#if	defined(CPU_X86_64)
typedf uint64_t addr_t;
#endif

struct address_structure {
    uint8_t address_space_id;    // 0 - system memory, 1 - system I/O
    uint8_t register_bit_width;
    uint8_t register_bit_offset;
    uint8_t reserved;
    uint64_t address;
} __attribute__((packed));
 
struct description_table_header {
    char signature[4];    // 'HPET' in case of HPET table
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oemid[6];
    uint64_t oem_tableid;
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
} __attribute__((packed));
 
struct hpet_description_table_header {
    uint8_t hardware_rev_id;
    uint8_t comparator_count:5;
    uint8_t counter_size:1;
    uint8_t reserved:1;
    uint8_t legacy_replacement:1;
    uint16_t pci_vendor_id;
    addr_t address;
    uint8_t hpet_number;
    uint16_t minimum_tick;
    uint8_t page_protection;
} __attribute__((packed));

#endif	// !defined(__machine_hpet_h)
