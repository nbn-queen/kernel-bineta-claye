#include <k/kstd.h>
#include <string.h>
#include "multiboot.h"
#include "io.h"

#include "gdt.h"

struct gdt_r gdtr;
struct gdt_entry gdt[6];



// Set the value of one GDT entry

void init_gdt( u32 base, u32 limite, u8 type, u8 dpl,s32 index)
{
    gdt[index].lim0_15 = (limite & 0xffff);
    gdt[index].base0_15 = (base & 0xffff);
    gdt[index].base16_23 = (base & 0xff0000) >> 16;
    gdt[index].type = type;
    gdt[index].s =1;
    gdt[index].dpl = dpl;
    gdt[index].p =1;
    gdt[index].lim16_19 = (limite & 0xf0000) >> 16;
    gdt[index].avl = 0;
    gdt[index].l=0;
    gdt[index].db=1;
    gdt[index].g=1;
    gdt[index].base24_31 = (base & 0xff000000) >> 24;
}



//Initialise the global descriptor table.

void load(void)
{
  memset(gdt,0x0,5);
  init_gdt(0x0, 0x0, 0x0, 0x0, 0);      /* Null segment*/
  init_gdt(0x0, 0xfffff, 0xA, 0x0, 1); /* kernel code */
  init_gdt(0x0, 0xfffff, 0x3, 0x0, 2); /* kernel data */
  //init_gdt(0x0, 0xfffff, 0xff, 0x0d, &gdt[3]);    /* user code */
 // init_gdt(0x0, 0xfffff, 0xF3, 0x0d, &gdt[4]);   /* user data */

  gdtr.base = (u32)&gdt;
  gdtr.limit = sizeof(gdt) - 1;

    asm volatile("lgdt %0\n"
    : /* no output */
    : "m" (gdtr)
    : "memory");
}

void load_cr0_seg_and_cs()
{
    __asm__(
    "   movl %cr0, %eax\n"
    "   or $1, %eax\n" //only enable protection set
    "   movl %eax, %cr0\n"
    "   movw $0x10, %ax\n" // 2 << 3 = 16 = 0x10
    "   movw %ax, %ss\n"
    "   movw %ax, %ds\n"
    "   movw %ax, %es\n"
    "   movw %ax, %fs\n"
    "   movw %ax, %gs\n"
    "   pushl $0x08\n" // 1 << 3 = 8 = 0x08
    "   pushl $1f\n"
    "   lret\n"
    "   1:\n"
    );
}
