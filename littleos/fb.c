    /* FrameBuffer Driver */


    #include "io.h"
    #include "fb.h"



    /* The I/O ports */
    #define FB_COMMAND_PORT         0x3D4
    #define FB_DATA_PORT            0x3D5

    /* The I/O port commands */
    #define FB_HIGH_BYTE_COMMAND    14
    #define FB_LOW_BYTE_COMMAND     15

    #define FB_ROWS     25
    #define FB_COLS     80

    static unsigned int currentPos = 0;
    static char *fb = (char *) 0x000B8000;

    /** fb_move_cursor:
     *  Moves the cursor of the framebuffer to the given position
     *
     *  @param pos The new position of the cursor
     */

    static void fb_move_cursor(unsigned short pos)
    {
        outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
        outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        outb(FB_DATA_PORT,    pos & 0x00FF);
        currentPos = pos;
    }

    void fb_move_cursor_to(unsigned int row, unsigned int col) 
    {
        fb_move_cursor( (unsigned short) row*FB_COLS + col );
    }



    /** fb_write_cell:
     *  Writes a character with the given foreground and background to position i
     *  in the framebuffer.
     *
     *  @param i  The location in the framebuffer
     *  @param c  The character
     *  @param fg The foreground color
     *  @param bg The background color
     */
    static void fb_write_cell(unsigned short i, char c, char fg, char bg)
    {
        unsigned int position = i *2;
        fb[position] = c;
        fb[position + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
    }


    static void fb_write_char(char c) 
    {
        if (c != '\n') {
            fb_write_cell(currentPos, c, FB_BLACK, FB_WHITE);
        }

        if (c == '\n') {
            fb_move_cursor( (currentPos - (currentPos%FB_COLS)) + FB_COLS );
        }
        else {
            fb_move_cursor(currentPos+1);
        }
    }
    /*
    static void fb_scroll()
    {
        int cell = 0;
        for (int i = 0; i < FB_ROWS; i++) {
            for (int j = 0; i < FB_COLS; j++) {
                fb_write_cell( cell, ' ', FB_WHITE, FB_DARK_GREY );
                cell++;
            }
        }
        fb_move_cursor_to(0,0);
    }
    */
    void fb_clear()
    {
        int cell = 0;
        for (int i = 0; i < FB_ROWS; i++) {
            for (int j = 0; j < FB_COLS; j++) {
                fb_write_cell( cell, ' ', FB_BLACK, FB_WHITE );
                cell++;
            }
        }
        fb_move_cursor_to(0,0);
    }

    int fb_write(char *s) 
    {
        int i = 0;

        while (s[i] != '\0') {
            fb_write_char( s[i] );
            i++;
        }

        return 0;

    }