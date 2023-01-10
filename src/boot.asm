/* Declare constants for the multboot header */

.set ALIGN,     1 << 0             /* Make sure to align on page boundaries */
.set MEMINFO,   1 << 1             /* Provide memory map */
.set FLAGS,     ALIGN | MEMINFO    /* Multiboot flags */
.set MAGIC,     0x1BADB002         /* magic number */
.set CHECKSUM, -(MAGIC + FLAGS)    /* Checksum of all this to prove we are multiboot */

/*
    This is where the multiboot header is declared,
    it's what marks your program as a kernel
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/*
    We need to set the Stack Pointer register as it is not set automatically,
    on x86 the stack grows downwards, we allocate 64kb for the stack and create
    a symbol at the top for it. The stack also has to be aligned on 16 byte boundaries
*/

.section .bss
.align 16

stack_bottom:
.skip 65536
stack_top:

/*
    The linker script is told to jump to the _start label,
    so when the Kernel is loaded execution starts here.
*/

.section .text
.global _start
.type _start, @function
_start:
            /*
                We are now in 32-bit Protected mode.
                * Interrupts are disabled
                * Paging is disabled
                * Processor state is as described in the multiboot standard
                We now have full power over the CPU
            */

            /* Set up the stack pointer register,
               necessary as any language (C for example) cannot work without a stack
            */

            mov $stack_top, %esp

            /*
                This place right here is a good place to initialize GDT Tables,
                Paging, or any sort of important CPU features. C++ Features such as
                Global constructors and exceptions will require runtime support.
            */

            /* Code here!!! */

            /*
                Enter the high-level kernel. Keep in mind the stack has to be 16 byte aligned
                at the time of the call intruction for this call to function.
            */

            call kernel_main

            /*
                If we're done with OS execution, disable interrupts (with 'cli' = Clear Interrupt enable in eflags)
                Then wait for the next interrupt with 'hlt', and because there will be none, it just hangs the computer
                if by any chance any sort of interruption happens and we get past the halt, jump back to the halt instruction
            */

            cli
hlt_loop:   hlt
            jmp hlt_loop


/*
    Set the size of the _start symbol to the current location minus its start.
    Useful for debugging or when implementing call tracing.
*/
.size _start, . - _start
