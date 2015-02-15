    #include "fb.h"
    #include "sp.h"


	int kmain() {

        fb_init();
        fb_writez_text("Welcome to ARDA\n");

        serial_configure(COM1);
        serial_write(COM1, "It's working... it's working!");


		return 0;
	}