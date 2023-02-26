//#include "drivers/serial/serial.h"
#include "kernel_main.h"

#import "arch/port.m"
#import "drivers/serial/serial.h"
#import "drivers/serial/serial.m"

@implementation KernelMain 

- (id) init {
    serial_port port;

    serial_port_create(SERIAL_COM1, &port);
    serial_port_write_string(&port, "Hello, Objective-C world!");

    return self;
}

@end

static void __objc_gnu_init(void);

void kernel_main() {
    __objc_gnu_init();

    [KernelMain init];
} 