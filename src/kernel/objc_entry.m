#include "drivers/serial/serial.h"

@interface KernelMain 

- (id) init;

@end

@implementation KernelMain 

- (id) init {
    serial_port port = {
        .port = SERIAL_COM1
    };

    serial_port_write_string(&port, "Hello, Objective-C world!");

    return self;
}

@end

static void __objc_gnu_init(void);

void objc_entry() {
    __objc_gnu_init();
    [KernelMain init];
}