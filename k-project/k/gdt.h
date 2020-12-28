#ifndef GDT_H
#define GDT_H

struct gdt_entry{

    int lim0_15 : 16;
    int base0_15 : 16;
    int  base16_23 : 8;
    int  type :4 ;
    int s : 1;
    int dpl: 2;
    int p : 1;
    int lim16_19 : 4;
    int avl :1;
    int l : 1;
    int db :1;
    int g :1;
    int  base24_31:8;
}__attribute__((packed));


struct gdt_r{
    u16 limit;
    u32 base;
}__attribute__((packed));

void init_gdt( u32 base, u32 limite, u8 type, u8 dpl, s32 index);
void load(void);
void load_cr0_seg_and_cs();
#endif

