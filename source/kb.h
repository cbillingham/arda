    #ifndef KB_H
    #define KB_H
    
    void keyboard_install();
    void keyboard_handler(struct cpu_state cpu, struct idt_info info, struct stack_state stack);

    #endif /* KB */