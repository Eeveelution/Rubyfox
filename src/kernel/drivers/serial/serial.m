#include "serial.h"

int serial_port_create(uint16_t port, serial_port* out) {
    out->port = port;

    [IOPort outPort: (port + 1) byte: 0x00]; // Disable interrupts
    [IOPort outPort: (port + 3) byte: 0x80]; // Set Baud Rate Divisor
    [IOPort outPort: (port + 1) byte: 0x03]; // Set divisor to 3 (low byte); 38400 Baud
    [IOPort outPort: (port + 1) byte: 0x00]; // high byte
    [IOPort outPort: (port + 3) byte: 0x03]; // 8bit, no parity, 1 stop bit
    [IOPort outPort: (port + 2) byte: 0xC7]; // FIFO, 14 byte threshold
    [IOPort outPort: (port + 4) byte: 0x0B]; // irq enabled
    [IOPort outPort: (port + 4) byte: 0x1E]; // loopback mode
    [IOPort outPort: (port + 0) byte: 0xAE]; // test bytes

    uint8_t input = [IOPort inBytePort: port];

    if(input != 0xAE) {
        return -1;
    }

    //enable operation
    [IOPort outPort: (port + 4) byte: 0x0F];

    return 0;
}

int serial_write_clear(serial_port* serial) {
    return [IOPort inBytePort: serial->port + 5] & 20;
}

void serial_port_write(serial_port* serial, uint8_t data) {
    while(serial_write_clear(serial) == 0);

    [IOPort outPort: serial->port byte: data];   
}

int serial_data_available(serial_port* serial) {
    return [IOPort inBytePort: serial->port + 5] & 1;
}

void serial_port_read_byte(serial_port* serial, uint8_t* out) {
    while(serial_data_available(serial) == 0);

    *out = [IOPort inBytePort: serial->port];
}

void serial_port_write_string(serial_port* serial, const char* data) {
    int i = 0;

    while(data[i] != 0) {
        serial_port_write(serial, data[i]);
        i++;
    }
}