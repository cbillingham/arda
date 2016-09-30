
extern interrupt_handler

global enable_interrupts
global disable_interrupts

%macro interrupt_noerrorcode 1  ; define a macro, taking one parameter
  global interrupt%1            ; %1 accesses the first parameter.
  interrupt%1:
    cli
    push    byte 0
    push    byte %1
    jmp     interrupt_common_stub
%endmacro

%macro interrupt_errorcode 1
  global interrupt%1
  interrupt%1:
    cli
    push    byte %1
    jmp     interrupt_common_stub
%endmacro

interrupt_noerrorcode 0
interrupt_noerrorcode 1
interrupt_noerrorcode 2
interrupt_noerrorcode 3
interrupt_noerrorcode 4
interrupt_noerrorcode 5
interrupt_noerrorcode 6
interrupt_noerrorcode 7
interrupt_errorcode   8
interrupt_noerrorcode 9
interrupt_errorcode   10
interrupt_errorcode   11
interrupt_errorcode   12
interrupt_errorcode   13
interrupt_errorcode   14
interrupt_noerrorcode 15
interrupt_noerrorcode 16
interrupt_noerrorcode 17
interrupt_noerrorcode 18
interrupt_noerrorcode 19
interrupt_noerrorcode 20
interrupt_noerrorcode 21
interrupt_noerrorcode 22
interrupt_noerrorcode 23
interrupt_noerrorcode 24
interrupt_noerrorcode 25
interrupt_noerrorcode 26
interrupt_noerrorcode 27
interrupt_noerrorcode 28
interrupt_noerrorcode 29
interrupt_noerrorcode 30
interrupt_noerrorcode 31

;IRQs

interrupt_noerrorcode 32
interrupt_noerrorcode 33
interrupt_noerrorcode 34
interrupt_noerrorcode 35
interrupt_noerrorcode 36
interrupt_noerrorcode 37
interrupt_noerrorcode 38
interrupt_noerrorcode 39
interrupt_noerrorcode 40
interrupt_noerrorcode 41
interrupt_noerrorcode 42
interrupt_noerrorcode 43
interrupt_noerrorcode 44
interrupt_noerrorcode 45
interrupt_noerrorcode 46
interrupt_noerrorcode 47

section .text:

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.

interrupt_common_stub:

   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10             ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call interrupt_handler

   pop eax                  ; reload the original data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa                     ; Pops edi,esi,ebp...
   add esp, 8               ; Cleans up the pushed error code and pushed ISR number
   sti
   iret                     ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret