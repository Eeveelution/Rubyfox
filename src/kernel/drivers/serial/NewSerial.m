#import <KObject.m>

typedef enum COMPortNum {
    COM1 = 0x3F8,
    COM2 = 0x2F8,
    COM3 = 0x3E8,
    COM4 = 0x2F8,
    COM5 = 0x5F8,
    COM6 = 0x4F8,
    COM7 = 0x5E8,
    COM8 = 0x4E8,
} COMPortNum;

@interface COMPort : KObject {
    unsigned char _initialized;
    COMPortNum _port;
}

+ (instancetype) newPort: (COMPortNum) port;
- (instancetype) initializePort: (COMPortNum) port;

- (void) writeBytes: (unsigned char*) bytes numBytes: (unsigned int) numBytes;

@end

@implementation COMPort : KObject

+ (instancetype) newPort: (COMPortNum) port {
    return [[COMPort alloc] initializePort: port];
}

- (instancetype) initializePort: (COMPortNum) port {
    if(self->_initialized) {
        return (COMPort*) 0;
    }

    self->_port = port;

    return self;
}

- (void) writeBytes: (unsigned char*) bytes numBytes: (unsigned int) numBytes {

}

@end