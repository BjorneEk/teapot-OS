#ifndef FONT_H
#define FONT_H

#include "../utils/include/int.h"

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
#define INVALID_IDX          55 /// a index outside of the range covvered by FONT5X7

#define FONT_LENGTH 50
#define FONT_WIDTH  5
#define FONT_HEIGHT 7

///
///   5 x 7 font containing the following characters in order
///
///	ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ0123456789.,:;!?
///

extern char * font_supported_chars;
extern uint8_t FONT5X7[50][7][5];

#endif /* FONT_H */