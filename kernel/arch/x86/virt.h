#if	!defined(__machine_virt_h)
#define	__machine_virt_h

// Intel Extensions
#define IA32_VMX_BASIC          0x480
#define IA32_VMX_CR0_FIXED0     0x486
#define IA32_VMX_CR0_FIXED1     0x487
#define IA32_VMX_CR4_FIXED0     0x488
#define IA32_VMX_CR4_FIXED1     0x489
 
extern void md_vmxon(void);

#endif	// !defined(__machine_virt_h)
