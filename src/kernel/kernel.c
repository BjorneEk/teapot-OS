

///
/// @author Gustaf Franzén :: https://github.com/BjorneEk
/// main teapot-OS kernel
///

#include "drivers/include/vga.h"
#include "drivers/include/int.h"

void delay(uint32_t length) {
	for (size_t i = 0; i < length; i++) {
		__asm__ __volatile__("nop");
	}
}
void main() {


	delay(0xfffffff);
	write_vga_640x480();
	//char * video_memory = (char*) 0xb8000;
	//*video_memory = 'X';
	//*(video_memory+2) = 'X';
	//for(;;) { }
}
