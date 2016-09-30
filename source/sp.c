	/* Serial Port Driver */

	#include "io.h"
    #include "string.h"


    /* The I/O ports */

    /* All the I/O ports are calculated relative to the data port. This is because
     * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
     * order, but they start at different values.
     */

    #define SERIAL_DATA_PORT(base)          (base)
    #define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
    #define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
    #define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
    #define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

    /* The I/O port commands */

    /* SERIAL_LINE_ENABLE_DLAB:
     * Tells the serial port to expect first the highest 8 bits on the data port,
     * then the lowest 8 bits will follow
     */
    #define SERIAL_LINE_ENABLE_DLAB         0x80
    #define BAUD_RATE 						0x01

    /** serial_configure_baud_rate:
     *  Sets the speed of the data being sent. The default speed of a serial
     *  port is 115200 bits/s. The argument is a divisor of that number, hence
     *  the resulting speed becomes (115200 / divisor) bits/s.
     *
     *  @param com      The COM port to configure
     *  @param divisor  The divisor
     */
    static void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
    {
        outb(SERIAL_LINE_COMMAND_PORT(com),
             SERIAL_LINE_ENABLE_DLAB);
        outb(SERIAL_DATA_PORT(com),
             (divisor >> 8) & 0x00FF);
        outb(SERIAL_DATA_PORT(com),
             divisor & 0x00FF);
    }

        /** serial_configure_line:
     *  Configures the line of the given serial port. The port is set to have a
     *  data length of 8 bits, no parity bits, one stop bit and break control
     *  disabled.
     *
     *  @param com  The serial port to configure
     */



    static void serial_configure_line(unsigned short com)
    {
        /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
         * Content: | d | b | prty  | s | dl  |
         * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
         */
        outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
    }


    static void serial_configure_buffer(unsigned short com)
    {
        /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
		 * Content: | lvl | bs | r | dma | clt | clr | e |
         * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
         */
        outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
    }

    static void serial_configure_modem(unsigned short com)
    {
        /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
		 * Content: | lvl | bs | r | dma | clt | clr | e |
         * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
         */
        outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
    }


    /** serial_is_transmit_fifo_empty:
     *  Checks whether the transmit FIFO queue is empty or not for the given COM
     *  port.
     *
     *  @param  com The COM port
     *  @return 0 if the transmit FIFO queue is not empty
     *          1 if the transmit FIFO queue is empty
     */
    static int serial_is_transmit_fifo_empty(unsigned short com)
    {
        /* 0x20 = 0010 0000 */
        return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
    }

    static void serial_write_char(unsigned short com, char data)
    {
        while( !serial_is_transmit_fifo_empty(com) ) {
            //wait
        }
        outb( SERIAL_DATA_PORT(com), data );
    }

    void serial_write(unsigned short com, char *data)
    {
        for (int i = 0; i < strlen(data); i++) {
            serial_write_char(com, data[i]);
        }
    }

    /* TODO: Write serial read function
    void serial_read(uint8_t serial_read(uint16_t com);
    {

    }
    */

    void serial_configure(unsigned short com)
    {
        serial_configure_baud_rate(com, BAUD_RATE);
        serial_configure_line(com);
        serial_configure_buffer(com);
        serial_configure_modem(com);
    }