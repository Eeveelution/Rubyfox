@interface KernelMain 

- (id) init;

@end

@implementation KernelMain 

- (id) init {
    return self;
}

@end

static void __objc_gnu_init(void);

void objc_entry() {
    __objc_gnu_init();
    [KernelMain init];
}