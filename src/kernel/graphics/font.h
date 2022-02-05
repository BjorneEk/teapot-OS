#ifndef FONT_H
#define FONT_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../libc/include/int.h"

#define OLD_FONT
#undef  OLD_FONT

#define ALPH_START 0x41
#define ALPH_END   0x5A
#define NUM_START  0x30
#define NUM_END    0x39

#define NUM_IDX_START        29
#define DOT_IDX              39
#define COMMA_IDX            40
#define COLON_IDX            41
#define SEMICOLON_IDX        42
#define EXCLAMATION_MARK_IDX 43
#define QUESTION_MARK_IDX    44
#define PARANTHESIS_R_IDX    45
#define PARANTHESIS_L_IDX    46
#define SQ_BRACET_R_IDX      47
#define SQ_BRACET_L_IDX      48
#define DASH_IDX             49
#define PLUSS_IDX            50
#define STAR_IDX             51
#define SLASH_IDX            52
#define EQUALS_IDX           53
#define LESS_THAN_IDX        54
#define GREATER_THAN_IDX     55
#define INVALID_IDX          57 /// a index outside of the range covvered by FONT5X7

#define FONT_LENGTH 56
#define FONT_WIDTH  5
#define FONT_HEIGHT 7

///
///   5 x 7 font containing the following characters in order
///
///	ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ0123456789.,:;!?<>()[]=+-/*
///

/**
 *   struct used to pack a font character into a 7
 *   byte space instead of a 5 * 7 byte space;
 **/
typedef struct f_col {
	union {
		uint8_t byte_rep;
		struct {
			uint8_t p1 : 1;
			uint8_t p2 : 1;
			uint8_t p3 : 1;
			uint8_t p4 : 1;
			uint8_t p5 : 1;
			uint8_t p6 : 1;
			uint8_t p7 : 1;
			uint8_t zero : 1;
		};
	};
} f_col_t;

/**
 *   size of this font representation is 5 bytes instead of
 *   the 35 bytes a byte array would have needed
 **/
typedef struct font_char{
	f_col_t f[5];
} font_char_t;

extern char * font_supported_chars;

#ifdef OLD_FONT
extern const uint8_t FONT5X7[50][7][5];
#endif
#ifndef OLD_FONT
extern const font_char_t FONT5X7_COMPACT[];
#endif
uint16_t get_idx_from_char(uint8_t c);

uint8_t font_at(uint16_t i, uint8_t x, uint8_t y);

#endif /* FONT_H */
