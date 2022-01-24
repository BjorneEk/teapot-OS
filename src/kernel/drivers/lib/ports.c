
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////


#include "../include/ports.h"



uint8_t in_portb(uint16_t port) {
	uint8_t res;
	__asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
	return res;
}

void out_portb(uint16_t port, uint8_t data) {
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
