global loader                   ; the entry symbol for ELF

    ; setting up the multiboot headers for GRUB
    KERNEL_STACK_SIZE equ 4096 
    SEGMENT_OFFSET    equ 0x10
    MODULEALIGN equ 1<<0                    ; align loaded modules on page
                                            ; boundaries
    MEMINFO     equ 1<<1                    ; provide memory map
    FLAGS       equ MODULEALIGN | MEMINFO   ; the multiboot flag field
    MAGIC_NUMBER       equ 0x1BADB002              ; magic number for bootloader to
                                            ; find the header
    CHECKSUM    equ -(MAGIC_NUMBER + FLAGS)        ; checksum required

    global lgdt
    global lidt
    global loadSegments

    section .bss
    align 4                                     ; align at 4 bytes
    kernel_stack:                               ; label points to beginning of memory
        resb    KERNEL_STACK_SIZE               ; reserve stack for the kernel


    section .text                        ; start of the boot section
    align 4                              ; the code must be 4 byte aligned
        dd      MAGIC_NUMBER             ; write the magic number to the machine code
        dd      FLAGS                    ; write the align modules instruction
        dd      CHECKSUM                 ; and the checksum

    ;lgdt - load gdt
    lgdt:
        mov     eax, [esp + 4]
        lgdt    [eax]
        ret

    ;lidt - load idt
    lidt:
        mov     eax, [esp + 4]
        lidt    [eax]  
        sti        
        ret


    loadSegments:

        jmp     0x08:flush_cs

    flush_cs:
        mov     ax, SEGMENT_OFFSET
        mov     ds, ax
        mov     ss, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        ret


    loader:                     ; the loader label (defined as entry point in linker script)

        extern  kmain

        mov     esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the stack (end of memory area)
        push    ebx         ; pass multiboot module to kmain
        call    kmain       ; call main kernel code


    .loop:
        jmp .loop                   ; loop forever