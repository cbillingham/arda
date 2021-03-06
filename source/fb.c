    /* FrameBuffer Driver */

    #include "io.h"
    #include "fb.h"
    #include "string.h"

    // This is the frame buffer base address.
    #define FB_BASE_ADDR 0x000B8000

    // A convenient define which gives us a char pointer to the frame buffer
    #define FB_CHAR_PTR ((char *) FB_BASE_ADDR)

    // A define that gives us a short ptr to the frame buffer.  Cells are 2 bytes wide so
    // this makes the index more natural for operating at the cell level.
    #define FB_SHORT_PTR ((unsigned short *) FB_BASE_ADDR)

    #define FB_WIDTH 80
    #define FB_HEIGHT 25

    #define FB_CMD_CURSOR_HIGH_BYTE 0x0E
    #define FB_CMD_CURSOR_LOW_BYTE 0x0F

    #define FB_COMMAND_PORT 0x3D4
    #define FB_DATA_PORT 0x3D5

    #define TAB_SPACE 4


    // A struct to keep track of the state of our frame buffer.
    struct {
      int row;
      int col;
      unsigned char fg_color;
      unsigned char bg_color;
      int scroll_mode;
    } fb_state;

    void fb_init() {
      fb_state.row = 0;
      fb_state.col = 0;
      fb_state.fg_color = FB_WHITE;
      fb_state.bg_color = FB_BLACK;
      fb_state.scroll_mode = 1;
    }

    void fb_move_cursor(unsigned char row, unsigned char col) {
      unsigned short pos = (row * FB_WIDTH) + col;
      outb(FB_COMMAND_PORT, FB_CMD_CURSOR_HIGH_BYTE);
      outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
      outb(FB_COMMAND_PORT, FB_CMD_CURSOR_LOW_BYTE);
      outb(FB_DATA_PORT, pos & 0x00FF);
    }

    void fb_write_cell(unsigned char row, unsigned char col, char c,
                       unsigned char fg_color, unsigned char bg_color) {
      char *cell = FB_CHAR_PTR;
      cell += (2 * FB_WIDTH * row) + (2 * col);

      cell[0] = c;
      cell[1] = ((bg_color << 4) & 0xf0) | (fg_color & 0x0f);
    }

    void clear_screen() {
      for (int i= 0; i < FB_HEIGHT; i++) {
        for (int j = 0; j < FB_WIDTH; j++) {
            fb_write_cell(i, j, ' ', fb_state.fg_color, fb_state.bg_color);
        }
      }
      fb_move_cursor(0, 0);
    }

    void scroll_framebuffer() {
      unsigned short *fb = FB_SHORT_PTR;
      int i;
      for (i = 0; i <= FB_WIDTH*(FB_HEIGHT-1); ++i) {
        unsigned short symbol = fb[i+FB_WIDTH];
        fb[i] = symbol;
      }
      // Blank the bottom line
      i = 24;
      for (int j = 0; j < FB_WIDTH; j++) {
            fb_write_cell(i, j, ' ', fb_state.fg_color, fb_state.bg_color);
      }
    }

    void fb_write_text(char *buffer) {
      for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] != '\n' && buffer[i] != '\t') {
            fb_write_cell(fb_state.row, fb_state.col, buffer[i],
                          fb_state.fg_color, fb_state.bg_color);
            fb_state.col++;
        }
        if (buffer[i] == '\n') {
            fb_state.col = 0;
            fb_state.row++;
        }
        if (buffer[i] == '\t') {
            fb_state.col = fb_state.col + TAB_SPACE;
        }
        if (fb_state.col >= FB_WIDTH) {
          fb_state.col = 0;
          fb_state.row++;
        }
        if (fb_state.row >= FB_HEIGHT) {
          if (fb_state.scroll_mode) {
            scroll_framebuffer();
            fb_state.row = FB_HEIGHT-1;
          } else {
            clear_screen();
            fb_state.row = 0;
          }
        }
      }
      // Once we're all done writing the string pop the cursor to its new position.
      fb_move_cursor(fb_state.row, fb_state.col);
    }

    void fb_write_dec(unsigned int n)
    {

        if (n == 0)
        {
            fb_write_cell(fb_state.row, fb_state.col, '0',
                            fb_state.fg_color, fb_state.bg_color);
            return;
        }

        unsigned int dec = n;
        char c[32];
        int i = 0;
        while (dec > 0)
        {
            c[i] = '0' + dec%10;
            dec /= 10;
            i++;
        }
        c[i] = '\0';

        char c2[32];
        c2[i--] = 0;
        int j = 0;
        while(i >= 0)
        {
            c2[i--] = c[j++];
        }
        fb_write_text(c2);

    }