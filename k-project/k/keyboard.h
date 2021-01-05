#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "multiboot.h"
#include "io.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

static u8 keys_map[128] =
{
    [8] = '\b',
    [9] = '\t',
    //[13] = ,  Enter
   // [16] = ,  shift
   // [17] = ,  ctrl
   // [18] = ,  Alt
   // [19] = ,  Pause/break
   // [20] = ,  Caps Lock
   // [27] = ,  Esc
   // [33] = ,  Page Up
   // [34] = ,  Page down 
   // [35] = ,  End
   // [36] = ,  Home
   // [37] = ,  Arrow left
    //[38] = ,  Arrow Up
    //[39] = ,   Arrow right 
    //[40] = ,  Arrow Down 
    //[45] = ,  insert
    //[46] = ,  delete
    [48] = '0',   
    [49] = '1',
    [50] = '2',
    [51] = '3',
    [52] = '4',
    [53] = '5',
    [54] = '6',
    [55] = '7',
    [56] = '8',
    [57] = '9',
    [65] = 'a',
    [66] = 'b',
    [67] = 'c',
    [68] = 'd',
    [69] = 'e',
    [70] = 'f',
    [71] = 'g',
    [72] = 'h',
    [73] = 'i',
    [74] = 'j',
    [75] = 'k',
    [76] = 'l',
    [77] = 'm',
    [78] = 'n',
    [79] = 'o',
    [80] = 'p',
    [81] = 'q',
    [82] = 'r',
    [83] = 's',
    [84] = 't',
    [85] = 'u',
    [86] = 'v',
    [87] = 'w',
    [88] = 'x',
    [89] = 'u',
    [90] = 'z',
}

#endif


