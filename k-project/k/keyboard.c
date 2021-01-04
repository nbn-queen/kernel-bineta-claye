#include"io.h"
#include<stdio.h>
//#include"/include/k/kstd.h"
#include"gdt.h"
#include"pic.h"

int getkey(){
    //initializing the PIC
    init_pic();
    //Reading Scancode from I/O port 0x60
    int scancode = inb(0x60);
    outb(0x60, scancode);



}
