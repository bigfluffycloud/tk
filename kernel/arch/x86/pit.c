#include <type.h>
#include <machine/asm.h>
#include <machine/pit.h>
#include <machine/pic.h>
#include <cons.h>
static uint8_t task = 0;
static uint8_t last_task = 0;

void set_task(uint8_t i) {
   if (!last_task)
      return;

   task = i;
}

void enable_task(void) {
   last_task = 1;
   task = 1;
}

// Crappy but at least lets us see timers are workin
static int tick_phase;
static char ticks[4] = { '.', ',', ':', '*' };

void md_pit_tick(void) {
   // Show a changing character at the top-right corner of console
   if (tick_phase == 5)
      tick_phase = 0;
   cons.buf[cons.width] = ticks[tick_phase];
   tick_phase++;

   // try to switch tasks
   if (!task) {
      asm volatile("add $0x1c, %esp");
      asm volatile("pusha");
      md_pic_eoi(0);
      asm volatile("popa");
      asm volatile("iret");
   } else {
      // XXX: Run scheduler here
//      scheduler_run();
   }
}

static inline void __pit_send_cmd(uint8_t cmd) {
    md_outb(PIT_REG_CMD, cmd);
}

static inline void __pit_send_data(uint16_t data, uint8_t counter) {
    uint8_t port = (counter == PIT_OCW_COUNTER_0) ? PIT_REG_COUNTER0 : 
                     ((counter == PIT_OCW_COUNTER_1) ? PIT_REG_COUNTER1 : PIT_REG_COUNTER2);
    md_outb(port, (uint8_t)data);
}

static inline uint8_t __pit_read_data(uint16_t counter) {
    uint8_t port =  (counter==PIT_OCW_COUNTER_0) ? PIT_REG_COUNTER0 :
                     ((counter==PIT_OCW_COUNTER_1) ? PIT_REG_COUNTER1 : PIT_REG_COUNTER2);
    return md_inb(port);
}

static void pit_start_counter(uint32_t freq, uint8_t counter, uint8_t mode) {
    if (freq == 0)
       return;

    cons_printf("Starting counter %d with frequency %dHz\n", counter/0x40, freq);

    // send ocw
    uint16_t divisor = (uint16_t)(1193181 / (uint16_t)freq);
    uint8_t ocw = 0;
    ocw = (ocw & ~PIT_OCW_MASK_MODE) | mode;
    ocw = (ocw & ~PIT_OCW_MASK_RL) | PIT_OCW_RL_DATA;
    ocw = (ocw & ~PIT_OCW_MASK_COUNTER) | counter;
    __pit_send_cmd(ocw);

    // set rate
    __pit_send_data(divisor & 0xff, 0);
    __pit_send_data((divisor >> 8) & 0xff, 0);
}

void md_pit_init(void) {
    cons_colour(CONS_RED, CONS_BLACK);
    cons_write("*");
    cons_colour(CONS_LTGREY, CONS_BLACK);
    cons_write(" pit: irq#0 (int#32) is now PIT_IRQ");
    pit_start_counter( 200, PIT_OCW_COUNTER_0, PIT_OCW_MODE_SQUAREWAVEGEN);
    cons_colour(CONS_GREEN, CONS_BLACK);
    cons_write("\tOK\n");
}
