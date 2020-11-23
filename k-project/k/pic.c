#include <k/kstd.h>

#include "multiboot.h"
#include "io.h"
#include "idt.h"
/*

    0x20, the master PIC’s port A
    0x21, the master PIC’s port B
    0xA0, the slave PIC’s port A
    0xA1, the slave PIC’s port B
*/

void init_pic(void)
{
  /* ICW1 */
	outb(0x20 , 0x11);
	outb(0xA0 , 0x11);

/* ICW2 */
	outb(0x21 , 0x20);
	outb(0xA1 , 0x28);

    /* ICW3 */
	outb(0x21 ,0x04); //  decimal value 
	outb(0xA1 ,0x02); //  bit number

    /* ICW4 */
	outb(0x21 , 0x01);
	outb(0xA1 , 0x01);
	
}

