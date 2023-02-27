#include "KObject.m"

#import "arch/Port.m"
#import "drivers/serial/serial.h"
#import "drivers/serial/serial.m"

@interface KernelMain : KObject

+ (id) init;

@end

@implementation KernelMain 

+ (id) init {
    serial_port port;

    int result = serial_port_create(SERIAL_COM1, &port);
    serial_port_write_string(&port, "Hello, Objective-C world!\n");

    return self;
}

@end

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

static void __objc_gnu_init();

void kernel_main() {
    __objc_gnu_init();

    [KernelMain init];
} 

#pragma GCC diagnostic pop

