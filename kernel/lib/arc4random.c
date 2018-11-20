/*-
 * THE BEER-WARE LICENSE
 *
 * <dan@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff.  If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.
 *
 * Dan Moschuk
 */

#include <type.h>
#include <stdlib.h>
#include <string.h>
#include <lib/arc4random.h>
#define	ARC4_RESEED_BYTES 65536
#define	ARC4_RESEED_SECONDS 300
#define	ARC4_KEYBYTES (256 / 8)

static uint8_t arc4_i, arc4_j;
static int arc4_numruns = 0;
static uint8_t arc4_sbox[256];
//static time_t arc4_t_reseed;
static struct mtx arc4_mtx;

static uint8_t arc4_randbyte(void);

/* If the entropy device is not loaded, make a token effort to
 * provide _some_ kind of randomness. This should only be used
 * inside other RNG's, like arc4random(9).
 */
static int read_random(void *buf, int count) {
   unsigned long randval;
   int size, i;

   /* srandom() is called in kern/init_main.c:proc0_post() */
   /* Fill buf[] with random(9) output */
   for (i = 0; i < count; i+= (int)sizeof(unsigned long)) {
       randval = random();
       size = MIN(count - i, sizeof(unsigned long));
       memmove(&((char *)buf)[i], &randval, (size_t)size);
   }

   return (count);
}

static __inline void arc4_swap(uint8_t *a, uint8_t *b) {
   uint8_t c;

   c = *a;
   *a = *b;
   *b = c;
}	

/*
 * Stir our S-box.
 */
static void arc4_randomstir(void) {
   uint8_t key[256];
   int r, n;
//   struct timeval tv_now;

   /*
    * XXX read_random() returns unsafe numbers if the entropy
    * device is not loaded -- MarkM.
    */
   r = read_random(key, ARC4_KEYBYTES);
//   getmicrouptime(&tv_now);
//   mtx_lock(&arc4_mtx);
   /* If r == 0 || -1, just use what was on the stack. */
   if (r > 0) {
      for (n = r; n < sizeof(key); n++)
          key[n] = key[n % r];
   }

   for (n = 0; n < 256; n++) {
      arc4_j = (arc4_j + arc4_sbox[n] + key[n]) % 256;
      arc4_swap(&arc4_sbox[n], &arc4_sbox[arc4_j]);
   }

   arc4_i = arc4_j = 0;

   /* Reset for next reseed cycle. */
//   arc4_t_reseed = tv_now.tv_sec + ARC4_RESEED_SECONDS;
   arc4_numruns = 0;

   /*
    * Throw away the first N words of output, as suggested in the
    * paper "Weaknesses in the Key Scheduling Algorithm of RC4"
    * by Fluher, Mantin, and Shamir.  (N = 256 in our case.)
    */
   for (n = 0; n < 256*4; n++)
      arc4_randbyte();

//   mtx_unlock(&arc4_mtx);
}

/*
 * Initialize our S-box to its beginning defaults.
 */
static void arc4_init(void) {
   int n;

//   mtx_init(&arc4_mtx, "arc4_mtx", NULL, MTX_DEF);
   arc4_i = arc4_j = 0;

   for (n = 0; n < 256; n++)
      arc4_sbox[n] = (uint8_t) n;

//   arc4_t_reseed = 0;
}

/*
 * Generate a random byte.
 */
static uint8_t arc4_randbyte(void) {
	uint8_t arc4_t;

	arc4_i = (arc4_i + 1) % 256;
	arc4_j = (arc4_j + arc4_sbox[arc4_i]) % 256;

	arc4_swap(&arc4_sbox[arc4_i], &arc4_sbox[arc4_j]);

	arc4_t = (arc4_sbox[arc4_i] + arc4_sbox[arc4_j]) % 256;
	return arc4_sbox[arc4_t];
}

/*
 * MPSAFE
 */
void arc4rand(void *ptr, unsigned int len, int reseed) {
   unsigned char *p;
//   struct timeval tv;

//   getmicrouptime(&tv);

//   if (reseed || (arc4_numruns > ARC4_RESEED_BYTES) ||
//       (tv.tv_sec > arc4_t_reseed))
      arc4_randomstir();

//   mtx_lock(&arc4_mtx);
   arc4_numruns += len;
   p = ptr;

   while (len--)
      *p++ = arc4_randbyte();

//   mtx_unlock(&arc4_mtx);
}

uint32_t arc4random(void) {
   uint32_t ret;

   arc4rand(&ret, sizeof ret, 0);
   return ret;
}
