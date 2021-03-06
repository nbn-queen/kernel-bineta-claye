#include <k/kstd.h>
#include <stdio.h>
#include <string.h>
#include "multiboot.h"
#include "io.h"
#include "idt.h"
#include "keyboard.h"


func interrupt_handlers[256] = {0};


void set_interrupt_tab (u8 n, func f)
{
    interrupt_handlers[n] = f;
}



static char* exceptions[32] = {
   "Division by Zero",
   "Debug exception",
   "Non Maskable Interrupt",
   "Breakpoint",
   "Overflow",
   "Bound Range Exceeded",
   "Invalid Opcode",
   "Device Not Available",
   "Double fault",
   "Coprocessor",
   "Invalid TSS",
   "Segment not present",
   "Stack Segment Fault",
   "General Protection Fault",
   "Page Fault",
   "(Intel Reserved)",
   "x87 FPU (Math Fault)",
   "Alignment Check",
   "Machine Check",
   "SMD Floating Point Ex.",
   "Virtualization Ex.",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)",
   "(Intel Reserved)"
};


struct idt_ptr   idtr;
struct idt_entry idt[256];

u32 tick = 0;


void idt_set (u32 base, u16 sel, u8 flags , u8 num)
{
    idt[num].offset0_15 = base & 0xffff;
    idt[num].seg_sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].offset16_31 = (base >> 16) & 0xffff; 
}


void init_idt()
{
    idtr.base = (u32)idt;
    idtr.limit = sizeof(idt) - 1;

    // isr entries


    idt_set((u32)isr0 , SEG_SEL, FLAGS,0);
    idt_set((u32)isr1 , SEG_SEL, FLAGS,1);
    idt_set((u32)isr2 , SEG_SEL, FLAGS,2);
    idt_set((u32)isr3 , SEG_SEL, FLAGS,3);
    idt_set((u32)isr4 , SEG_SEL, FLAGS,4);
    idt_set((u32)isr5 , SEG_SEL, FLAGS,5);
    idt_set((u32)isr6 , SEG_SEL, FLAGS,6);
    idt_set((u32)isr7 , SEG_SEL, FLAGS,7);
    idt_set((u32)isr8 , SEG_SEL, FLAGS,8);
    idt_set((u32)isr9 , SEG_SEL, FLAGS,9);
    idt_set((u32)isr10 , SEG_SEL, FLAGS,10);
    idt_set((u32)isr11 , SEG_SEL, FLAGS,11);
    idt_set((u32)isr12 , SEG_SEL, FLAGS,12);
    idt_set((u32)isr13 , SEG_SEL, FLAGS,13);
    idt_set((u32)isr14 , SEG_SEL, FLAGS,14);
    idt_set((u32)isr15 , SEG_SEL, FLAGS,15);
    idt_set((u32)isr16 , SEG_SEL, FLAGS,16);
    idt_set((u32)isr17 , SEG_SEL, FLAGS,17);
    idt_set((u32)isr18 , SEG_SEL, FLAGS,18);
    idt_set((u32)isr19 , SEG_SEL, FLAGS,19);
    idt_set((u32)isr20 , SEG_SEL, FLAGS,20);
    idt_set((u32)isr21 , SEG_SEL, FLAGS,21);
    idt_set((u32)isr22 , SEG_SEL, FLAGS,22);
    idt_set((u32)isr23 , SEG_SEL, FLAGS,23);
    idt_set((u32)isr24 , SEG_SEL, FLAGS,24);
    idt_set((u32)isr25 , SEG_SEL, FLAGS,25);
    idt_set((u32)isr26 , SEG_SEL, FLAGS,26);
    idt_set((u32)isr27 , SEG_SEL, FLAGS,27);
    idt_set((u32)isr28 , SEG_SEL, FLAGS,28);
    idt_set((u32)isr29 , SEG_SEL, FLAGS,29);
    idt_set((u32)isr30 , SEG_SEL, FLAGS,30);
    idt_set((u32)isr31 , SEG_SEL, FLAGS,31);

    // IRQ

    idt_set((u32)irq0 , SEG_SEL, FLAGS,32);
    idt_set((u32)irq1 , SEG_SEL, FLAGS,33);
    idt_set((u32)irq2 , SEG_SEL, FLAGS,34);
    idt_set((u32)irq3 , SEG_SEL, FLAGS,35);
    idt_set((u32)irq4 , SEG_SEL, FLAGS,36);
    idt_set((u32)irq5 , SEG_SEL, FLAGS,37);
    idt_set((u32)irq6 , SEG_SEL, FLAGS,38);
    idt_set((u32)irq7 , SEG_SEL, FLAGS,39);
    idt_set((u32)irq8 , SEG_SEL, FLAGS,40);
    idt_set((u32)irq9 , SEG_SEL, FLAGS,41);
    idt_set((u32)irq10 , SEG_SEL, FLAGS,42);
    idt_set((u32)irq11 , SEG_SEL, FLAGS,43);
    idt_set((u32)irq12 , SEG_SEL, FLAGS,44);
    idt_set((u32)irq13 , SEG_SEL, FLAGS,45);
    idt_set((u32)irq14 , SEG_SEL, FLAGS,46);
    idt_set((u32)irq15 , SEG_SEL, FLAGS,47);
    

  

    //load
    __asm__ volatile("lidt %0\n"
      : /* no output */
      : "m" (idtr)
      : "memory");
}

unsigned long gettick(void)
{
        gettick ();
        printf("Tick: %d\n",tick);
        return tick;

}

int getkey(void) 
{
    char status;
    int scancode;
  
    status = inb (KEYBOARD_STATUS_PORT);
    if (status & 0x01) // check if a the key is pressed
    {
        scancode = inb(KEYBOARD_DATA_PORT);
        if (scancode < 0)
            return -1;
    //   char k = keys_map[scancode]; Our map
      printf("%x \n", scancode);
    return scancode;  
    }
    return -1;
}
    


void generic_c_handler(registers_t regs)
{
    if(regs.nb < 32)
    {
        
        printf("[!] Exception: %s (%u)\n", exceptions[regs.nb], regs.nb);   
    }
    else
    {   
        tick ++; 
        if (regs.nb - 32 == 0)
        {
            printf("recieved a irq0 \n");
            gettick();
        }
             
        else if(regs.nb - 32 == 1)
        {
            printf("recieved irq1\n");
            getkey();
            outb(0x20,0x20);
        }
             
        else
             printf("[!] Interrupt no handler for the moment \n");

    }
}
