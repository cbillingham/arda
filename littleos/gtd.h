    #ifndef GTD_H
    #define GTD_H

    struct gdt_entry
    {
        unsigned short limit_low;
        unsigned short base_low;
        unsigned char base_middle;
        unsigned char access;
        unsigned char granularity;
        unsigned char base_high;
    } __attribute__((packed));


    struct gdt_ptr
    {
        unsigned short limit;
        unsigned int base;
    } __attribute__((packed));


    //Described in loader.s
    void lgdt(unsigned int gdt);

    //Described in loader.s
    void loadSegments();

    void gdt_install();

    #endif /* IO_H */