    #ifndef IDT_H
    #define IDT_H

    // PIC - from http://wiki.osdev.org/8259_PIC
    #define PIC1            0x20    /* IO base address for master PIC */
    #define PIC2            0xA0    /* IO base address for slave PIC */
    #define PIC1_COMMAND    PIC1
    #define PIC1_DATA       (PIC1+1)
    #define PIC2_COMMAND    PIC2
    #define PIC2_DATA       (PIC2+1)
    #define PIC1_START_INTERRUPT 0x20 /* Master PIC after remapping*/
    #define PIC2_START_INTERRUPT 0x28 /* Slave PIC after remapping*/

    #define PIC_EOI         0x20    /* End-of-interrupt command code */

    #define ICW1_ICW4       0x01    /* ICW4 (not) needed */
    #define ICW1_SINGLE     0x02    /* Single (cascade) mode */
    #define ICW1_INTERVAL4  0x04    /* Call address interval 4 (8) */
    #define ICW1_LEVEL      0x08    /* Level triggered (edge) mode */
    #define ICW1_INIT       0x10    /* Initialization - required! */

    #define ICW4_8086       0x01    /* 8086/88 (MCS-80/85) mode */
    #define ICW4_AUTO       0x02    /* Auto (normal) EOI */
    #define ICW4_BUF_SLAVE  0x08    /* Buffered mode/slave */
    #define ICW4_BUF_MASTER 0x0C    /* Buffered mode/master */
    #define ICW4_SFNM       0x10    /* Special fully nested (not) */

    struct idt_entry_struct
    {
       unsigned short base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
       unsigned short sel;                 // Kernel segment selector.
       unsigned char  always0;             // This must always be zero.
       unsigned char  flags;               // More flags. See documentation.
       unsigned short base_hi;             // The upper 16 bits of the address to jump to.
    } __attribute__((packed));
    typedef struct idt_entry_struct idt_entry_t;

    struct idt_ptr {
        unsigned short limit;
        unsigned int base;
    } __attribute__((packed));
    typedef struct idt_ptr idt_ptr_t;

    //Described in loader.s
    void lidt(unsigned int idt_ptr);


    void idt_install();


    // These extern directives let us access the addresses of our ASM ISR handlers.
    extern void interrupt0 ();
    extern void interrupt1 ();
    extern void interrupt2 ();
    extern void interrupt3 ();
    extern void interrupt4 ();
    extern void interrupt5 ();
    extern void interrupt6 ();
    extern void interrupt7 ();
    extern void interrupt8 ();
    extern void interrupt9 ();
    extern void interrupt10();
    extern void interrupt11();
    extern void interrupt12();
    extern void interrupt13();
    extern void interrupt14();
    extern void interrupt15();
    extern void interrupt16();
    extern void interrupt17();
    extern void interrupt18();
    extern void interrupt19();
    extern void interrupt20();
    extern void interrupt21();
    extern void interrupt22();
    extern void interrupt23();
    extern void interrupt24();
    extern void interrupt25();
    extern void interrupt26();
    extern void interrupt27();
    extern void interrupt28();
    extern void interrupt29();
    extern void interrupt30();
    extern void interrupt31();
    extern void interrupt32();
    extern void interrupt33();
    extern void interrupt34();
    extern void interrupt35();
    extern void interrupt36();
    extern void interrupt37();
    extern void interrupt38();
    extern void interrupt39();
    extern void interrupt40();
    extern void interrupt41();
    extern void interrupt42();
    extern void interrupt43();
    extern void interrupt44();
    extern void interrupt45();
    extern void interrupt46();
    extern void interrupt47();
    
    #endif /* IDT_H */