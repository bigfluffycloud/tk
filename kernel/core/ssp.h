#if	!defined(__core_ssp_h)
#define	__core_ssp_h

extern long __stack_chk_guard[8];
extern void __stack_chkguard_setup(void);
extern void __stack_chk_fail(void);

#endif	// !defined(__core_ssp_h)
