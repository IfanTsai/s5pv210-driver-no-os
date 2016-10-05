#ifndef __KEY_H__
#define __KEY_H__

#define GPH0CON         (*((volatile unsigned int *)0xe0200c00))
#define GPH0DAT         (*((volatile unsigned int *)0xe0200c04))
#define GPH2CON         (*((volatile unsigned int *)0xe0200c40))
#define GPH2DAT         (*((volatile unsigned int *)0xe0200c44))

#define EXT_INT_0_CON   (*((volatile unsigned int *)0xe0200e00))
#define EXT_INT_2_CON   (*((volatile unsigned int *)0xe0200e08))
#define EXT_INT_0_MASK  (*((volatile unsigned int *)0xe0200f00))
#define EXT_INT_2_MASK  (*((volatile unsigned int *)0xe0200f08))
#define EXT_INT_0_PEND  (*((volatile unsigned int *)0xe0200f40))
#define EXT_INT_2_PEND  (*((volatile unsigned int *)0xe0200f48))

#define SW5             (GPH0DAT & (0x1 << 2))
#define SW6             (GPH0DAT & (0x1 << 3))
#define SW7             (GPH2DAT & (0x1 << 0))
#define SW8             (GPH2DAT & (0x1 << 1))
#define SW9             (GPH2DAT & (0x1 << 2))
#define SW10            (GPH2DAT & (0x1 << 3))
    
void key_init();
void key_polling();
void key_interrupt_init();
void do_SW5();
void do_SW6();
void do_SW7_to_10();


#endif
