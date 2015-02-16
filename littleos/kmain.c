    #include "fb.h"
    #include "sp.h"
    #include "io.h"
    #include "gtd.h"


	int kmain() {

        gdt_install();


        fb_init();
        clear_screen();
        fb_write_text("Welcome to ARDA!\nBooting...\n");

        serial_configure(COM1);
        serial_write(COM1, "It's working... it's working!");


		return 0;
	}