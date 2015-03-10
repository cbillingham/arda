    #include "interrupt.h"
    #include "idt.h"
    #include "fb.h"
    #include "sp.h"
    #include "kb.h"

    static void *irq_routines[16] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    /* This installs a custom IRQ handler for the given IRQ */
    void irq_install_handler(int irq, void (*handler)(cpu_state_t cpu, idt_info_t info, stack_state_t stack))
    {
        irq_routines[irq] = handler;
    }

    /* This clears the handler for a given IRQ */
    void irq_uninstall_handler(int irq)
    {
        irq_routines[irq] = 0;
    }

    static char *exception_messages[] =
    {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",

        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",

        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",

        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"
    };

    void interrupt_handler(cpu_state_t cpu, idt_info_t info, stack_state_t stack) {

        if (info.idt_index < 20) {
            fb_write_text("\n***********\nException: ");
            fb_write_text(exception_messages[info.idt_index]);
            //fb_write_text("\nSystem Halted\n");
            //for (;;); //for loop to halt system
        }

        if (info.idt_index >= 32 && info.idt_index <= 47) {

            /* If the IDT entry that was invoked was greater than 40
            *  (meaning IRQ8 - 15), then we need to send an EOI to
            *  the slave controller */
            if (info.idt_index >= 40)
            {
                outb(0xA0, 0x20);
            }

            /* In either case, we need to send an EOI to the master
            *  interrupt controller too */
            outb(0x20, 0x20);
            
            /* This is a blank function pointer */
            void (*handler)(cpu_state_t cpu, idt_info_t info, stack_state_t stack);

            /* Find out if we have a custom handler to run for this
            *  IRQ, and then finally, run it */
            handler = irq_routines[info.idt_index - 32];
            if (handler)
            {
                handler(cpu, info, stack);
            }

        }

    }