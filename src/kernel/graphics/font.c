
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "font.h"
#include "../libc/include/malloc.h"


#define OLD_FONT
#undef OLD_FONT

char * font_supported_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ0123456789.,:;!?";

/**
 * switching to the new compact font saved 4Kb
 **/

const font_char_t FONT5X7_COMPACT[] = {
	(font_char_t){
		0b0111111,
		0b1000010,
		0b1000010,
		0b1000010,
		0b0111111,
	}, (font_char_t){
		0b1111111,
		0b1000101,
		0b1000101,
		0b1000101,
		0b0111010,
	}, (font_char_t){
		0b0011100,
		0b0100010,
		0b1000001,
		0b1000001,
		0b0100010,
	}, (font_char_t){
		0b1111111,
		0b1000001,
		0b1000001,
		0b0100010,
		0b0011100,
	}, (font_char_t){
		0b0000100,
		0b1111111,
		0b1000101,
		0b1000001,
		0b1100011,
	}, (font_char_t){
		0b0000100,
		0b1111111,
		0b1000100,
		0b1000000,
		0b1100000,
	}, (font_char_t){
		0b0011100,
		0b0100010,
		0b1000001,
		0b1000101,
		0b0100110,
	}, (font_char_t){
		0b0000010,
		0b1111111,
		0b0000010,
		0b0000010,
		0b1111111,
	}, (font_char_t){
		0b1000001,
		0b1000001,
		0b1111111,
		0b1000001,
		0b1000001,
	}, (font_char_t){
		0b0000010,
		0b0000001,
		0b0000001,
		0b1000001,
		0b1111110,
	}, (font_char_t){
		0b1111111,
		0b0000100,
		0b0000100,
		0b0011010,
		0b1100001,
	}, (font_char_t){
		0b1111111,
		0b0000001,
		0b0000001,
		0b0000001,
		0b0000011,
	}, (font_char_t){
		0b1111111,
		0b0100000,
		0b0010000,
		0b0100000,
		0b1111111,
	}, (font_char_t){
		0b1111111,
		0b0100000,
		0b0010000,
		0b0001000,
		0b1111111,
	}, (font_char_t){
		0b0111110,
		0b1000001,
		0b1000001,
		0b1000001,
		0b0111110,
	}, (font_char_t){
		0b1111111,
		0b1000010,
		0b1000010,
		0b0100100,
		0b0011000,
	}, (font_char_t){
		0b0111110,
		0b1000001,
		0b1000101,
		0b1000010,
		0b0111101,
	}, (font_char_t){
		0b1111111,
		0b1000010,
		0b1000010,
		0b0100101,
		0b0011000,
	}, (font_char_t){
		0b0111010,
		0b1000101,
		0b1000101,
		0b1000101,
		0b0100010,
	}, (font_char_t){
		0b1100000,
		0b1000000,
		0b1111111,
		0b1000000,
		0b1100000,
	}, (font_char_t){
		0b1111110,
		0b0000001,
		0b0000001,
		0b0000001,
		0b1111110,
	}, (font_char_t){
		0b1111100,
		0b0000010,
		0b0000001,
		0b0000010,
		0b1111100,
	}, (font_char_t){
		0b1111111,
		0b0000010,
		0b0000100,
		0b0000010,
		0b1111111,
	}, (font_char_t){
		0b1100011,
		0b0010100,
		0b0001000,
		0b0010100,
		0b1100011,
	}, (font_char_t){
		0b1111000,
		0b0000100,
		0b0000011,
		0b0000100,
		0b1111000,
	}, (font_char_t){
		0b1100011,
		0b1000101,
		0b1001001,
		0b1010001,
		0b1100011,
	}, (font_char_t){
		0b0001111,
		0b1010010,
		0b1010010,
		0b0010010,
		0b0001111,
	}, (font_char_t){
		0b1001111,
		0b1010010,
		0b0010010,
		0b1010010,
		0b1001111,
	}, (font_char_t){
		0b1001110,
		0b1010001,
		0b0010001,
		0b1010001,
		0b1001110,
	}, (font_char_t){
		0b0111110,
		0b1000101,
		0b1001001,
		0b1010001,
		0b0111110,
	}, (font_char_t){
		0b0000000,
		0b0100001,
		0b1111111,
		0b0000001,
		0b0000000,
	}, (font_char_t){
		0b0110011,
		0b1000101,
		0b1001001,
		0b1010001,
		0b0100011,
	}, (font_char_t){
		0b1100010,
		0b1000001,
		0b1010001,
		0b1101010,
		0b1000100,
	}, (font_char_t){
		0b0011000,
		0b0101000,
		0b1001001,
		0b0011111,
		0b0001001,
	}, (font_char_t){
		0b1110110,
		0b1010001,
		0b1010001,
		0b1010010,
		0b1001100,
	}, (font_char_t){
		0b0011110,
		0b0110001,
		0b1010001,
		0b1010001,
		0b0001110,
	}, (font_char_t){
		0b1100100,
		0b1000100,
		0b1001111,
		0b1010100,
		0b1100100,
	}, (font_char_t){
		0b0101110,
		0b1010001,
		0b1010001,
		0b1010001,
		0b0101110,
	}, (font_char_t){
		0b0111000,
		0b1000100,
		0b1000101,
		0b1000110,
		0b0111100,
	}, (font_char_t){
		0b0000000,
		0b0000000,
		0b0000001,
		0b0000000,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0000001,
		0b0000110,
		0b0000000,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0000000,
		0b0100010,
		0b0000000,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0000001,
		0b0100110,
		0b0000000,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0000000,
		0b1111101,
		0b0000000,
		0b0000000,
	}, (font_char_t){
		0b0110000,
		0b1010000,
		0b1000101,
		0b1001000,
		0b0110000,
	}, (font_char_t){
		0b0000000,
		0b1000001,
		0b1000001,
		0b0111110,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0111110,
		0b1000001,
		0b1000001,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b1000001,
		0b1111111,
		0b0000000,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0000000,
		0b1111111,
		0b1000001,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0001000,
		0b0001000,
		0b0001000,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0001000,
		0b0011100,
		0b0001000,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0101000,
		0b0010000,
		0b0101000,
		0b0000000,
	}, (font_char_t){
		0b0000001,
		0b0000110,
		0b0001000,
		0b0110000,
		0b1000000,
	}, (font_char_t){
		0b0000000,
		0b0100100,
		0b0100100,
		0b0100100,
		0b0000000,
	}, (font_char_t){
		0b1000010,
		0b1000010,
		0b0100100,
		0b0011000,
		0b0000000,
	}, (font_char_t){
		0b0000000,
		0b0011000,
		0b0100100,
		0b1000010,
		0b1000010,
	}
};


#ifdef OLD_FONT
const uint8_t FONT5X7[50][7][5] = {
	{
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1},
		{1,0,0,0,1},
	}, {
		{1,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,0},
		{1,0,0,0,1},
		{1,1,1,1,0},
	}, {
		{0,0,1,1,0},
		{0,1,0,0,1},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{0,1,0,0,1},
		{0,0,1,1,0},
	}, {
		{1,1,1,0,0},
		{1,0,0,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,1,0},
		{1,1,1,0,0},
	}, {
		{0,1,1,1,1},
		{0,1,0,0,1},
		{0,1,0,0,0},
		{0,1,0,0,0},
		{1,1,1,0,0},
		{0,1,0,0,1},
		{0,1,1,1,1},
	}, {
		{0,1,1,1,1},
		{0,1,0,0,1},
		{0,1,0,0,0},
		{0,1,0,0,0},
		{1,1,1,0,0},
		{0,1,0,0,0},
		{0,1,0,0,0},
	}, {
		{0,0,1,1,0},
		{0,1,0,0,1},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,0,0,1,1},
		{0,1,0,0,1},
		{0,0,1,1,0},
	}, {
		{0,1,0,0,1},
		{0,1,0,0,1},
		{0,1,0,0,1},
		{0,1,0,0,1},
		{0,1,0,0,1},
		{1,1,1,1,1},
		{0,1,0,0,1},
	}, {
		{1,1,1,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,1,1,1},
	}, {
		{0,0,0,1,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{1,0,0,0,1},
		{0,1,1,1,0},
	}, {
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,1,0},
		{1,0,0,1,0},
		{1,1,1,0,0},
		{1,0,0,1,0},
		{1,0,0,0,1},
	}, {
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,0,0,0,1},
		{1,1,1,1,1},
	}, {
		{1,0,0,0,1},
		{1,1,0,1,1},
		{1,0,1,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
	}, {
		{1,0,0,0,1},
		{1,1,0,0,1},
		{1,0,1,0,1},
		{1,0,0,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
	}, {
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,1,1,0},
	}, {
		{1,1,1,0,0},
		{1,0,0,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,1,0},
		{1,1,1,0,0},
		{1,0,0,0,0},
	}, {
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,1,0,1},
		{1,0,0,1,0},
		{0,1,1,0,1},
	}, {
		{1,1,1,0,0},
		{1,0,0,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,1,0},
		{1,1,1,0,0},
		{1,0,0,1,0},
	},
	{
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{0,1,1,1,0},
		{1,0,0,0,1},
		{0,1,1,1,0},
	}, {
		{1,1,1,1,1},
		{1,0,1,0,1},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
	}, {
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,1,1,0},
	}, {
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,0,1,0},
		{0,0,1,0,0},
	}, {
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,1,0,1},
		{1,1,0,1,1},
		{1,0,0,0,1},
	}, {
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,0,1,0},
		{0,0,1,0,0},
		{0,1,0,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
	}, {
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,0,1,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
	}, {
		{1,1,1,1,1},
		{1,0,0,0,1},
		{0,0,0,1,0},
		{0,0,1,0,0},
		{0,1,0,0,0},
		{1,0,0,0,1},
		{1,1,1,1,1},
	}, {
		{0,1,1,0,0},
		{0,0,0,0,0},
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1},
		{1,0,0,0,1},
	}, {
		{1,1,0,1,1},
		{0,0,0,0,0},
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1},
		{1,0,0,0,1},
	}, {
		{1,1,0,1,1},
		{0,0,0,0,0},
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,1,1,0},
	}, {
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,1,1},
		{1,0,1,0,1},
		{1,1,0,0,1},
		{1,0,0,0,1},
		{0,1,1,1,0},
	}, {
		{0,0,1,0,0},
		{0,1,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,1,1,1,0},
	}, {
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,1,0},
		{0,0,1,0,0},
		{0,1,0,0,0},
		{1,0,0,0,1},
		{1,1,1,1,1},
	}, {
		{1,1,1,1,1},
		{1,0,0,1,0},
		{0,0,1,0,0},
		{0,0,0,1,0},
		{0,0,0,0,1},
		{1,0,0,1,0},
		{0,1,1,0,0},
	}, {
		{0,0,1,0,0},
		{0,1,0,0,0},
		{1,0,0,1,0},
		{1,1,1,1,1},
		{0,0,0,1,0},
		{0,0,0,1,0},
		{0,0,1,1,1},
	}, {
		{1,1,1,1,1},
		{1,0,0,0,0},
		{1,1,1,1,0},
		{0,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,1,0},
		{0,1,1,0,0},
	}, {
		{0,0,1,1,0},
		{0,1,0,0,0},
		{1,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,1,1,0},
	},
	{
		{1,1,1,1,1},
		{1,0,0,0,1},
		{0,0,0,1,0},
		{0,0,1,0,0},
		{1,1,1,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0},
	}, {
		{0,1,1,1,0},
		{1,0,0,0,1},
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,1,1,0},
	}, {
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{0,1,1,1,1},
		{0,0,0,1,0},
		{0,0,1,0,0},
	}, {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
	}, {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,1,0,0,0},
	}, {
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,0,0,0},
	}, {
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,1,0,0,0},
	}, {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
	}, {
		{0,1,1,1,0},
		{1,0,0,0,1},
		{1,1,0,0,1},
		{0,0,0,1,0},
		{0,0,1,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
	}, {
		{0,1,1,0,0},
		{0,0,0,1,0},
		{0,0,0,1,0},
		{0,0,0,1,0},
		{0,0,0,1,0},
		{0,0,0,1,0},
		{0,1,1,0,0},
	}, {
		{0,0,1,1,0},
		{0,1,0,0,0},
		{0,1,0,0,0},
		{0,1,0,0,0},
		{0,1,0,0,0},
		{0,1,0,0,0},
		{0,0,1,1,0},
	}, {
		{0,1,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,1,1,0,0},
	}, {
		{0,0,1,1,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,1,0},
	}, {
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,1,1,1,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
	}
};
#endif

#ifdef enable_syntax_highlighting_in_comment
/**
 *   to convert between old font chars and new font i used this function;
 **/
printf("const font_char_t FONT5X7_COMPACT[] = {\n");
printf("qp,qp,{\n", );
for (int i = 0; i < 50; i++) {
	for (int x = 0; x < 5; x++) {
		printf("{0b");
		for (int y = 0; y < 7; y++) {
			printf("%i", FONT5X7[i][y][x]);
		}
		printf("},\n");
	}
	printf("}, {\n");
}
#endif

/**
 *  function that returns the index in the font array in which
 *  the image of the char is located
 **/
uint16_t get_idx_from_char(uint8_t c) {
	if(c <= 0x40) {
		switch (c) {
			case ';': return SEMICOLON_IDX;
			case ':': return COLON_IDX;
			case '.': return DOT_IDX;
			case ',': return COMMA_IDX;
			case '?': return QUESTION_MARK_IDX;
			case '!': return EXCLAMATION_MARK_IDX;
			case ')': return PARANTHESIS_R_IDX;
			case '(': return PARANTHESIS_L_IDX;
			case '-': return DASH_IDX;
			case '+': return PLUSS_IDX;
			case '*': return STAR_IDX;
			case '/': return SLASH_IDX;
			case '=': return EQUALS_IDX;
			case '<': return LESS_THAN_IDX;
			case '>': return GREATER_THAN_IDX;
			default:
				if (c <= NUM_END && c >= NUM_START)
					return ((uint8_t)c - NUM_START) + NUM_IDX_START;
				return INVALID_IDX;
		}
	}
	if (c <= ALPH_END) return (uint8_t)c - ALPH_START;
	/// (0x61 - 0x41):  0x61: lower case a, 0x41 upper case a
	if(c >= 0x61 && c <= 0x7a) return (((uint8_t)c - (0x61 - 0x41)) - ALPH_START);
	if(c == ']') return SQ_BRACET_R_IDX;
	if(c == '[') return SQ_BRACET_L_IDX;

	return INVALID_IDX;
}

/**
 *  decompresses a column form the font image to a row
 *  in the array representation
 **/
uint8_t * decompress_col(font_char_t img, uint8_t col, uint8_t color) {
	uint8_t * res = malloc(5);
	for (size_t i = 0; i < 5; i++) {
		res[i] = (img.f[i].byte_rep & (1 << 7-col)) ? color : 0;
	}
}

void decompress_font_image(uint8_t *** res, font_char_t img, uint8_t color) {
	for (size_t i = 0; i < 7; i++) {
		(*res)[i] = decompress_col(img, i, color);
	}
}

uint8_t font_at(uint16_t i, uint8_t x, uint8_t y) {
	return (FONT5X7_COMPACT[i].f[x].byte_rep & (1 << 6-y)) ? 1 : 0;
}
