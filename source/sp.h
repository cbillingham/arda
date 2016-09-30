    #include "io.h"

	#ifndef SP_H
    #define SP_H

	#define COM1 0x3F8

	void serial_configure(unsigned short com);
	void serial_write(unsigned short com, char *data);
	// TODO: uint8_t serial_read(uint16_t com);


    #endif /* SP */