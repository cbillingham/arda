    #include "fb.h"


	int kmain() {

	    #define FB_GREEN     2
    	#define FB_DARK_GREY 8

    	fb_write_cell(0, 'A', FB_GREEN, FB_DARK_GREY);

    	fb_move_cursor(800);



		return 0;
	}