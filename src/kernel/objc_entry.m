@interface KernelMain 

+ (void) kernelMain;

@end

@implementation KernelMain 

+ (void) kernelMain {

}

@end

void objc_entry() {
    [KernelMain kernelMain];
}