#include "KObject.m"

#import "AppCodeCompat.h"

#import "arch/Port.m"
#import "drivers/serial/serial.h"
#import "drivers/serial/serial.m"
#import "drivers/serial/NewSerial.m"

@interface KernelMain : KObject

+ (void) init;

@end

@implementation KernelMain 

+ (void) init {
    id comPort = [COMPort newPort: COM1];

    [comPort writeBytes: 0 numBytes: 0];

    serial_port port;

    int result = serial_port_create(SERIAL_COM1, &port);
    serial_port_write_string(&port, "Hello, Objective-C world!\n");

    [comPort release];
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

