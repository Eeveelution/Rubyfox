#include "port.h"

inline void outb(uint16_t port, uint8_t val) {
    asm volatile (
        "outb %[data], %[port]"
        :
        : [data] "a" (val), 
          [port] "Nd" (port)
    );
}

inline uint8_t inb(uint16_t port) {
    uint8_t inByte = 0;

    asm volatile (
        "inb %[port], %[byte]"
        : [byte] "=a" (inByte)
        : [port] "Nd" (port)
    );

    return inByte;
}