
extern void objc_entry();

void kernel_main() {
    //uint16_t* vga_buffer = (uint16_t*) 0xB8000;
//
	//for(int y = 0; y < 25; y++) {
	//	for(int x = 0; x < 80; x++) {
	//		const int index = y * 80 + x;
	//		vga_buffer[index] = vga_entry(' ', 15);
	//	}
	//}
//
    //const char* message = "Hello, Rubyfox!\n";
    //size_t message_length = strlen(message);
//
    //for(size_t i = 0; i != message_length; i++) {
    //    vga_buffer[i] = vga_entry(message[i], 15);
    //}
//

    ////__objc_gnu_init();
    objc_entry();
//
    //for(size_t i = 0; i != message_length; i++) {
    //        serial_port_write(&com1, message[i]);
    //    }
//
    //while(true) {
    //    
    //}
}