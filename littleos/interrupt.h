    #ifndef INTERRUPT_H
    #define INTERRUPT_H


    void enable_interrupts();
    void disable_interrupts();

    struct idt_info {
        unsigned int idt_index;
        unsigned int error_code;
    } __attribute__((packed));
    typedef struct idt_info idt_info_t;

    struct cpu_state {
        unsigned int ds;
        unsigned int edi;
        unsigned int esi;
        unsigned int ebp;
        unsigned int esp;
        unsigned int ebx;
        unsigned int edx;
        unsigned int ecx;
        unsigned int eax;
    } __attribute__((packed));
    typedef struct cpu_state cpu_state_t;

    struct stack_state {
        unsigned int eip;
        unsigned int cs;
        unsigned int eflags;
        unsigned int user_esp;
        unsigned int user_ss;
    } __attribute__((packed));
    typedef struct stack_state stack_state_t;

    void interrupt_handler(cpu_state_t cpu, idt_info_t info, stack_state_t stack);
    void irq_install_handler(int irq, void (*handler)(cpu_state_t cpu, idt_info_t info, stack_state_t stack));
    void irq_uninstall_handler(int irq);

    #endif /* INTERRUPT_H */