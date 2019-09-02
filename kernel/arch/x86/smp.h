#if	!defined(__machine_smp_h)
#define	__machine_smp_h


#include <sys/stddef.h>
#include <sys/types.h>
typedef struct {
    // The Signature, must contain _MP_, and is present on a 16 byte boundary.
    uint8_t  Signature[4];
 
    // The address of the MP Configuration Table. 
    uint32_t MPConfigurationTable;
 
    // The length of the floating point structure table, in 16 byte units. This field *should* contain 0x01, meaning 16-bytes.
    uint8_t  Length;
 
    // The version number of the MP Specification. A value of 1 indicates 1.1, 4 indicates 1.4, and so on.
    uint8_t  Version;
 
    // The checksum of the Floating Point Structure. 
    uint8_t  Checksum;
 
    // Few feature bytes.
    uint8_t FeatureBytes[5];
} MPFloatingPoint;


#endif	// !defined(__machine_smp_h)
 