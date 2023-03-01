typedef struct {
    unsigned short pointer_low;
    unsigned short selector;
    unsigned char  zero;
    unsigned char  type_attributes;
    unsigned short pointer_high;
} InterruptDescriptor;

typedef struct {
    unsigned short limit;
    unsigned int   base;
} __attribute__((packed)) InterruptDescriptorTableRegister;

__attribute__((aligned(0x10))) static InterruptDescriptor idt[256];
static InterruptDescriptorTableRegister idtr;

__attribute__((noreturn)) void default_exception_handler() {
    __asm__ volatile ("cli; hlt");
}

@interface InterruptDescriptorTable

@end

@implementation InterruptDescriptorTable

@end