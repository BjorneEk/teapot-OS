#ifndef ISR_H
#define ISR_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

/**
 * Struct which aggregates many registers.
 * It matches exactly the pushes on interrupt.S From the bottom:
 * - Pushed by the processor automatically
 * - `push byte`s on the isr-specific code: error code, then int number
 * - All the registers by pusha
 * - `push eax` whose lower 16-bits contain DS
 **/
typedef struct {
	uint32_t ds; /* Data segment selector */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
	uint32_t int_no, err_code; /* Interrupt number and error code (if applicable) */
	uint32_t eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} registers_t;

void isr_install();

void isr_handler(registers_t *r);

typedef void (*isr_t)(registers_t *);

void register_interrupt_handler(uint8_t n, isr_t handler);

#endif /* ISR_H */
