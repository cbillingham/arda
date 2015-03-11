    #include "fb.h"
    #include "sp.h"
    #include "io.h"
    #include "gtd.h"
    #include "idt.h"
    #include "interrupt.h"
    #include "kb.h"


	void kmain() {

        gdt_install();
        idt_install();

        fb_init();
        clear_screen();
        fb_write_text("Welcome to ARDA!\n");

        serial_configure(COM1);
        serial_write(COM1, "It's working... it's working!");

        fb_write_text("\nTesting CPU interrupt handlers:\n");
        __asm__ __volatile__ ("int $0x3");
        __asm__ __volatile__ ("int $0x4");

        keyboard_install();

		return;
	}