#if	!defined(__lib_arc4random_h)
#define __lib_arc4random_h

extern uint32_t arc4random(void);
extern void arc4rand(void *ptr, unsigned int len, int reseed);

#endif	// !defined(__lib_arc4random_h)
