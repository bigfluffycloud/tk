#if	!defined(__dev_virtio_h)
#define	__dev_virtio_h

#include <sys/stdbool.h>
#include <sys/types.h>

#define QueueSize 64

#define	VIRTIO_VENDOR		0x1af4
#define	VIRTIO_DEV_MIN		0x1000
#define	VIRTIO_DEV_MAX		0x103f
#define	VIRTIO_SYS_NET		0x01
#define	VIRTIO_SYS_BLOCK	0x02
#define	VIRTIO_SYS_CONS		0x03
#define	VIRTIO_SYS_ENTROPY	0x04
#define	VIRTIO_SYS_MEMBALLOON	0x05
#define	VIRTIO_SYS_IOMEM	0x06
#define VIRTIO_SYS_RPMSG	0x07
#define	VIRTIO_SYS_SCSI_HOST	0x08
#define	VIRTIO_SYS_9P		0x09
#define	VIRTIO_SYS_WLAN		0x10

#define	VIRTIO_REG_DEVFEAT	0x00
#define	VIRTIO_REG_GUESTFEAT	0x04
#define	VIRTIO_REG_QUEUE_ADDR	0x08
#define VIRTIO_REG_QUEUE_SIZE	0x0c
#define	VIRTIO_REG_QUEUE_SEL	0x0e
#define	VIRTIO_REG_QUEUE_NOTIFY	0x10
#define	VIRTIO_REG_DEV_STATUS	0x12
#define VIRTIO_REG_ISR_STATUS	0x13

#define	VIRTIO_DEV_STATUS_ACK	0x01
#define	VIRTIO_DEV_STATUS_DRV_OK 0x02
#define	VIRTIO_DEV_STATUS_DRV_RDY 0x04
#define	VIRTIO_DEV_STATUS_DEV_ERR 0x40
#define VIRTIO_DEV_STATUS_DRV_FAIL 0x80

#define	VIRTIO_NET_DEV_REG_MAC1 0x14
#define VIRTIO_NET_DEV_REG_MAC2 0x15
#define VIRTIO_NET_DEV_REG_MAC3 0x16
#define VIRTIO_NET_DEV_REG_MAC4 0X17
#define VIRTIO_NET_DEV_REG_MAC5 0x18
#define VIRTIO_NET_DEV_REG_MAC6 0x19
#define VIRTIO_NET_DEV_REG_STATUS 0x1a

#define VIRTIO_BLOCK_DEV_REG_SECTORS 0x14
#define VIRTIO_BLOCK_DEV_MAX_SEG_SIZE 0x1c
#define VIRTIO_BLOCK_DEV_MAX_SEG_COUNT 0x20
#define VIRTIO_BLOCK_DEV_CYL_COUNT 0x24
#define VIRTIO_BLOCK_DEV_HEAD_COUNT 0x26
#define VIRTIO_BLOCK_DEV_SECTOR_COUNT 0x27
#define VIRTIO_BLOCK_DEV_BLOCK_LENGTH 0x28

struct VirtualQueue {
  struct {
    long Address; // 64-bit address of the buffer on the guest machine.
    int Length;   // 32-bit length of the buffer.
    short Flags;  // 1:Next field contains linked buffer index.  2:Buffer is write-only (clear for read-only).  4:Buffer contains additional buffer addresses.
    short Next;   // If flag is set, contains index of next buffer in chain.
  } Buffers[QueueSize];

  struct {
    short Flags;            // 1: Do not trigger interrupts.
    short Index;            // Index of the next ring index to be used.  (Last available ring buffer index+1)
    short Ring[QueueSize];  // List of available buffer indexes from Buffers array above.
    short InterruptIndex;   // If enabled, device will trigger interrupt after this ring index has been processed.
  } Available;
  // XXX: Figure out the size for here, NOT 6...
  uint8_t Padding[6];  // Reserved

  // 4096 uint8_t alignment
  struct {
    short Flags;            // 1: Do not notify device when buffers are added to available ring.
    short Index;            // Index of the next ring index to be used.  (Last used ring buffer index+1)

    struct { 
      int Index;  // Index of the used buffer in the Buffers array above.
      int Length; // Total bytes written to buffer.
    } Ring[QueueSize];
    short InterruptIndex;   // If enabled, device will trigger interrupt after this ring index has been used.
  };
};

struct PacketHeader {
  uint8_t Flags;            // 1: Needs checksum
  uint8_t Segmentation;     // 0:None 1:TCPv4 3:UDP 4:TCPv6 0x80:ECN
  short HeaderLength;    // Size of header to be used during segmentation.
  short SegmentLength;   // Maximum segment size (not including header).
  short ChecksumStart;   // The position to begin calculating the checksum.
  short ChecksumOffset;  // The position after ChecksumStart to store the checksum.
  short BufferCount;     // Used when merging buffers.
};

struct BlockRequest {
  int Type;              // 0:Read 1:Write
  int Priority;          // 0:Low
  long Sector;
  uint8_t Data[255];
  uint8_t Status;           // 0:OK 1:Error 2:Unsupported
};
#endif	// !defined(__dev_virtio_h)
