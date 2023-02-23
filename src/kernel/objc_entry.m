//#include "drivers/serial/serial.h"
#include "arch/port.h"

#include <stddef.h>
#include <stdint.h>

@interface KernelMain 

- (id) init;

@end

@implementation KernelMain 

- (id) init {
    //serial_port port;

    //serial_port_create(SERIAL_COM1, &port);
    //serial_port_write_string(&port, "Hello, Objective-C world!");

    [IOPort outPort: 1 byte: 123];

    return self;
}

@end

static void __objc_gnu_init(void);

void objc_entry() {
    __objc_gnu_init();
    [KernelMain init];
} 