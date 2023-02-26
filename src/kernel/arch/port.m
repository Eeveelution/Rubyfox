#include <stdint.h>

@interface IOPort

- (void) outPort: (uint16_t) port byte: (uint8_t) byte;
- (void) outPort: (uint16_t) port word: (uint16_t) word;
- (void) outPort: (uint16_t) port long: (uint32_t) _long;

- (uint8_t) inBytePort: (uint16_t) port;
- (uint16_t) inWordPort: (uint16_t) port;
- (uint32_t) inLongPort: (uint16_t) port;

@end

@implementation IOPort 

- (void) outPort: (uint16_t) port byte: (uint8_t) byte {
    asm volatile (
        "outb %[data], %[port]"
        :
        : [data] "a" (byte), 
          [port] "Nd" (port)
    );
}

- (void) outPort: (uint16_t) port word: (uint16_t) word {
    asm volatile (
        "outw %[data], %[port]"
        :
        : [data] "a" (word), 
          [port] "Nd" (port)
    );
}

- (void) outPort: (uint16_t) port long: (uint32_t) _long {
    asm volatile (
        "outl %%eax, %%dx"
        :
        : "a" (_long), 
          "Nd" (port)
    );
}

- (uint8_t) inBytePort: (uint16_t) port {
    uint8_t inByte = 0;

    asm volatile (
        "inb %[port], %[byte]"
        : [byte] "=a" (inByte)
        : [port] "Nd" (port)
    );

    return inByte;
}

- (uint16_t) inWordPort: (uint16_t) port {
    uint16_t inWord = 0;

    asm volatile (
        "inw %[port], %[word]"
        : [word] "=a" (inWord)
        : [port] "Nd" (port)
    );

    return inWord;
}

- (uint32_t) inLongPort: (uint16_t) port {
    uint32_t inLong = 0;

    asm volatile (
        "inl %%dx, %%eax"
        : "=a" (inLong)
        : "Nd" (port)
    );

    return inLong;
}

@end