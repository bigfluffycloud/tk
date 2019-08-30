// Processor exceptions and stack traces
#include <machine/except.h>
#include <cons.h>

static void md_null_int(void) {
  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("Got interrupt!");
}

md_int_map md_int_tbl[] = {
  { 0x00, INT_FAULT,		"Div by 0",	&md_null_int },
  { 0x01, INT_TRAP|INT_FAULT,	"Debug",	&md_null_int },
  { 0x02, 0x0,			"NMI",		&md_null_int },
  { 0x03, INT_TRAP,		"Brkpt",	&md_null_int },
  { 0x04, INT_TRAP,		"Overflow",	&md_null_int },
  { 0x05, INT_FAULT,		"Bounds",	&md_null_int },
  { 0x06, INT_FAULT,		"Invalid opcode", &md_null_int },
  { 0x07, INT_FAULT,		"No FPU",	&md_null_int },
  { 0x08, INT_ABORT,		"Double fault", &md_null_int },
  { 0x09, INT_ABORT,		"FPU seg ovrrun", &md_null_int }, // <= 386 only
  { 0x0a, INT_FAULT,		"Invalid TSS",	&md_null_int },
  { 0x0b, INT_FAULT,		"Segment not present", &md_null_int },
  { 0x0c, INT_FAULT,		"Stack fault",	&md_null_int },
  { 0x0d, INT_FAULT,		"GPF",		&md_null_int },
  { 0x0e, INT_FAULT,		"Page fault",	&md_null_int },
  { 0x10, 0x0,			"Math fault", 	&md_null_int },
  { 0x11, INT_FAULT,		"Alignment",	&md_null_int },
  { 0X12, INT_ABORT,		"Machine Check", &md_null_int },
  { 0x13, INT_FAULT,		"SIMD FP",	&md_null_int }
};

void	md_isr_c(md_trap_frame frame) {
  cons_write("Got interrupt");
}

void	md_stack_dump(uint32_t MaxFrames) {
   // Stack contains:
   //  Second function argument
   //  First function argument (MaxFrames)
   //  Return address in calling function
   //  ebp of calling function (pointed to by current ebp)
   uint32_t *ebp = &MaxFrames - 2;

   cons_colour(CONS_YELLOW, CONS_BLUE);
   cons_clear();
   cons_write("Task Crashed :(\n\n");
   cons_write("Stack trace:\n");

   for (uint32_t frame = 0; frame < MaxFrames; ++frame) {
        uint32_t eip = ebp[1];

        if (eip == 0)
            // No caller on stack
            break;

        // Unwind to previous stack frame
        ebp = (uint32_t *)(ebp[0]);
        uint32_t *arguments = &ebp[2];
        cons_printf("  0x%lu     \n", eip);
    }
}
