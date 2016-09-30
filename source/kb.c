    #include "io.h"
    #include "interrupt.h"
    #include "fb.h"

    // TO DO: Backspace

    static unsigned char is_lshift_down       = 0;
    static unsigned char is_rshift_down       = 0;
    static unsigned char is_caps_lock_pressed = 0;


    unsigned char kbdus[128] =
    {
        0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
      '9', '0', '-', '=', '\b', /* Backspace */
      '\t',         /* Tab */
      'q', 'w', 'e', 'r',   /* 19 */
      't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     /* Enter key */
        0,          /* 29   - Control */
      'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
     '\'', '`',   0,        /* Left shift */
     '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
      'm', ',', '.', '/',   0,                  /* Right shift */
      '*',
        0,  /* Alt */
      ' ',  /* Space bar */
        0,  /* Caps lock */
        0,  /* 59 - F1 key ... > */
        0,   0,   0,   0,   0,   0,   0,   0,
        0,  /* < ... F10 */
        0,  /* 69 - Num lock*/
        0,  /* Scroll Lock */
        0,  /* Home key */
        0,  /* Up Arrow */
        0,  /* Page Up */
      '-',
        0,  /* Left Arrow */
        0,
        0,  /* Right Arrow */
      '+',
        0,  /* 79 - End key*/
        0,  /* Down Arrow */
        0,  /* Page Down */
        0,  /* Insert Key */
        0,  /* Delete Key */
        0,   0,   0,
        0,  /* F11 Key */
        0,  /* F12 Key */
        0,  /* All other keys are undefined */
    };

    

    static void toggle_left_shift(void)
    {
        is_lshift_down = is_lshift_down ? 0 : 1;
    }

    static void toggle_right_shift(void)
    {
        is_rshift_down = is_rshift_down ? 0 : 1;
    }

    static void toggle_caps_lock(void)
    {
        is_caps_lock_pressed = is_caps_lock_pressed ? 0 : 1;
    }

    static char handle_caps_lock(unsigned char ch)
    {
        if (ch >= 'a' && ch <= 'z') {
            return ch + 'A' - 'a';
        }
        return ch;
    }

    static char handle_shift(unsigned char ch)
    {
        /* Alphabetic characters */
        if (ch >= 'a' && ch <= 'z') {
            return ch + 'A' - 'a';
        }

        /* Number characters */
        switch (ch) {
            case '0':
                return ')';
            case '1':
                return '!';
            case '2':
                return '@';
            case '3':
                return '#';
            case '4':
                return '$';
            case '5':
                return '%';
            case '6':

                return '^';
            case '7':
                return '&';
            case '8':
                return '*';
            case '9':
                return '(';
            default:
                break;
        }

        /* Special charachters */
        switch (ch) {
            case '-':
                return '_';
            case '=':
                return '+';
            case '[':
                return '{';
            case ']':
                return '}';
            case '\\':
                return '|';
            case ';':
                return ':';
            case '\'':
                return '\"';
            case ',':
                return '<';
            case '.':
                return '>';
            case '/':
                return '?';
            case '`':
                return '~';
        }

        return ch;
    }

    /* Handles the keyboard interrupt */
    void keyboard_handler(__attribute__ ((unused)) struct cpu_state cpu, __attribute__ ((unused)) struct idt_info info, __attribute__ ((unused)) struct stack_state stack)
    {
        /* Read from the keyboard's data buffer */
        unsigned char scancode = inb(0x60);

        /* If the top bit of the byte we read from the keyboard is
        *  set, that means that a key has just been released */
        if (scancode & 0x80) {

            scancode &= 0x7F;
            switch (scancode) {
                case 0x2a:
                    toggle_left_shift();
                    break;
                case 0x36:
                    toggle_right_shift();
                    break;
                case 0x3a:
                    toggle_caps_lock();
                    break;
                default:
                    break;
            }
        }
        else {

            if (scancode == 0x2a) {
                toggle_left_shift();
            }
            else if (scancode == 0x36) {
                toggle_right_shift();
            }
            else {

                char ch = kbdus[scancode];

                if (is_caps_lock_pressed) {
                    ch = handle_caps_lock(ch);
                }

                if (is_lshift_down || is_rshift_down) {
                    ch = handle_shift(ch);
                }

                char str[2];
                str[0] = ch;
                str[1] = '\0';
                fb_write_text((char *) str);
            }
        }
    }

    /* Installs the keyboard handler into IRQ1 */
    void keyboard_install()
    {
        irq_install_handler(1, &keyboard_handler);
    }
