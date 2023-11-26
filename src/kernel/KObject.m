#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wobjc-root-class"

@interface KObject {

}

+ (instancetype) alloc;
- (void) release;

@end

@implementation KObject 

+ (instancetype) alloc {
    return self;
}

- (void) release {

}

@end

#pragma GCC diagnostic pop