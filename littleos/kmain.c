    #include "fb.h"
    #include "sp.h"


	int kmain() {

        fb_clear();
        fb_move_cursor_to(0,0);
        fb_write("Welcome to ARDA\n");

        serial_configure(COM1);
        serial_write(COM1, "It's working... it's working!");


		return 0;
	}