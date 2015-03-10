#include "idt.h"
#include "io.h"

#define IDT_INTERRUPT_GATE_TYPE 0
#define IDT_TRAP_GATE_TYPE      1

#define IDT_NUM_ENTRIES         256

idt_entry_t idt[IDT_NUM_ENTRIES];
idt_ptr_t  idt_ptr;

static void idt_set_gate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags);

static inline void io_wait() {

}

// from http://wiki.osdev.org/8259_PIC
static void PIC_remap(unsigned char offset1, unsigned char offset2) {
  unsigned char a1, a2;

  a1 = inb(PIC1_DATA);                        // save masks
  a2 = inb(PIC2_DATA);

  outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
  io_wait();
  outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
  io_wait();
  outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
  io_wait();
  outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
  io_wait();
  outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  io_wait();
  outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
  io_wait();

  outb(PIC1_DATA, ICW4_8086);
  io_wait();
  outb(PIC2_DATA, ICW4_8086);
  io_wait();

  outb(PIC1_DATA, a1);   // restore saved masks.
  outb(PIC2_DATA, a2);
}

void idt_install() {

    idt_ptr.limit = IDT_NUM_ENTRIES * sizeof(idt_entry_t) - 1;
    idt_ptr.base  = (unsigned int) &idt;

    idt_set_gate( 0, (unsigned int)interrupt0 , 0x08, 0x8E);
    idt_set_gate( 1, (unsigned int)interrupt1 , 0x08, 0x8E);
    idt_set_gate( 2, (unsigned int)interrupt2 , 0x08, 0x8E);
    idt_set_gate( 3, (unsigned int)interrupt3 , 0x08, 0x8E);
    idt_set_gate( 4, (unsigned int)interrupt4 , 0x08, 0x8E);
    idt_set_gate( 5, (unsigned int)interrupt5 , 0x08, 0x8E);
    idt_set_gate( 6, (unsigned int)interrupt6 , 0x08, 0x8E);
    idt_set_gate( 7, (unsigned int)interrupt7 , 0x08, 0x8E);
    idt_set_gate( 8, (unsigned int)interrupt8 , 0x08, 0x8E);
    idt_set_gate( 9, (unsigned int)interrupt9 , 0x08, 0x8E);
    idt_set_gate(10, (unsigned int)interrupt10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned int)interrupt11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned int)interrupt12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned int)interrupt13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned int)interrupt14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned int)interrupt15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned int)interrupt16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned int)interrupt17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned int)interrupt18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned int)interrupt19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned int)interrupt20 , 0x08, 0x8E);
    idt_set_gate(21, (unsigned int)interrupt21 , 0x08, 0x8E);
    idt_set_gate(22, (unsigned int)interrupt22 , 0x08, 0x8E);
    idt_set_gate(23, (unsigned int)interrupt23 , 0x08, 0x8E);
    idt_set_gate(24, (unsigned int)interrupt24 , 0x08, 0x8E);
    idt_set_gate(25, (unsigned int)interrupt25 , 0x08, 0x8E);
    idt_set_gate(26, (unsigned int)interrupt26 , 0x08, 0x8E);
    idt_set_gate(27, (unsigned int)interrupt27 , 0x08, 0x8E);
    idt_set_gate(28, (unsigned int)interrupt28 , 0x08, 0x8E);
    idt_set_gate(29, (unsigned int)interrupt29 , 0x08, 0x8E);
    idt_set_gate(30, (unsigned int)interrupt30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned int)interrupt31, 0x08, 0x8E);

    // Remap the irq table
    PIC_remap(PIC1_START_INTERRUPT, PIC2_START_INTERRUPT);


    /* IRQs */
    idt_set_gate( 32, (unsigned int)interrupt32, 0x08, 0x8E);
    idt_set_gate( 33, (unsigned int)interrupt33, 0x08, 0x8E);
    idt_set_gate( 34, (unsigned int)interrupt34, 0x08, 0x8E);
    idt_set_gate( 35, (unsigned int)interrupt35, 0x08, 0x8E);
    idt_set_gate( 36, (unsigned int)interrupt36, 0x08, 0x8E);
    idt_set_gate( 37, (unsigned int)interrupt37, 0x08, 0x8E);
    idt_set_gate( 38, (unsigned int)interrupt38, 0x08, 0x8E);
    idt_set_gate( 39, (unsigned int)interrupt39, 0x08, 0x8E);
    idt_set_gate( 40, (unsigned int)interrupt40, 0x08, 0x8E);
    idt_set_gate( 41, (unsigned int)interrupt41, 0x08, 0x8E);
    idt_set_gate( 42, (unsigned int)interrupt42, 0x08, 0x8E);
    idt_set_gate( 43, (unsigned int)interrupt43, 0x08, 0x8E);
    idt_set_gate( 44, (unsigned int)interrupt44, 0x08, 0x8E);
    idt_set_gate( 45, (unsigned int)interrupt45, 0x08, 0x8E);
    idt_set_gate( 46, (unsigned int)interrupt46, 0x08, 0x8E);
    idt_set_gate( 47, (unsigned int)interrupt47, 0x08, 0x8E);


    lidt((unsigned int) &idt_ptr);
}

static void idt_set_gate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags)
{
   idt[num].base_lo = base & 0xFFFF;
   idt[num].base_hi = (base >> 16) & 0xFFFF;

   idt[num].sel     = sel;
   idt[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt[num].flags   = flags /* | 0x60 */;
}
