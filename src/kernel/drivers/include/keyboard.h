#ifndef KEYBOARD_H
#define KEYBOARD_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#define KEY_A     0x1E
#define KEY_B     0x30
#define KEY_C     0x2E
#define KEY_D     0x20
#define KEY_E     0x12
#define KEY_F     0x21
#define KEY_G     0x22
#define KEY_H     0x23
#define KEY_I     0x17
#define KEY_J     0x24
#define KEY_K     0x25
#define KEY_L     0x26
#define KEY_M     0x32
#define KEY_N     0x31
#define KEY_O     0x18
#define KEY_P     0x19
#define KEY_Q     0x10
#define KEY_R     0x13
#define KEY_S     0x1F
#define KEY_T     0x14
#define KEY_U     0x16
#define KEY_V     0x2F
#define KEY_W     0x11
#define KEY_X     0x2D
#define KEY_Y     0x15
#define KEY_Z     0x2C

#define KEY_LEFT_ARROW             0x4B
#define KEY_RIGHT_ARROW            0x4D
#define KEY_UP_ARROW               0x48
#define KEY_DOWN_ARROW             0x50

#define KEY_MINUS                 0x0C
#define KEY_SEMICOLON             0x27
#define KEY_COMMA                 0x33
#define KEY_DOT                   0x34
#define KEY_SINGLE_QUOTE          0x28
#define KEY_BACKSLASH             0x2B
#define KEY_SLASH                 0x35
#define KEY_LSQARE_BRACKET        0x1A
#define KEY_RSQUARE_BRACET        0x1B
#define KEY_EQUALS                0x0D

#define KEY_ESCAPE                0x01
#define KEY_BACKSPACE             0x0E
#define KEY_TAB                   0x0F
#define KEY_ENTER                 0x1C
#define KEY_LCTRL                 0x1D
#define KEY_RCTRL                 0xE0
#define KEY_LSHIFT                0x2A
#define KEY_RSHIFT                0x36
#define KEY_LALT                  0x38
#define KEY_SPACE                 0x39
#define KEY_CAPS_LOCK             0x3A

#define KEY_LESS_THAN             0x29

#define KEY_F1                    0x3B
#define KEY_F2                    0x3C
#define KEY_F3                    0x3D
#define KEY_F4                    0x3E
#define KEY_F5                    0x3F
#define KEY_F6                    0x40
#define KEY_F7                    0x41
#define KEY_F8                    0x42
#define KEY_F9                    0x43
#define KEY_F10                   0x44
#define KEY_F11                   0x57
#define KEY_F12                   0x58

#define KEY_NUMLOCK               0x45
#define KEY_SCROLLLOCK            0x46

#define KEY_RELEASED_A     0x9E
#define KEY_RELEASED_B     0xB0
#define KEY_RELEASED_C     0xAE
#define KEY_RELEASED_D     0xA0
#define KEY_RELEASED_E     0x92
#define KEY_RELEASED_F     0xA1
#define KEY_RELEASED_G     0xA2
#define KEY_RELEASED_H     0xA3
#define KEY_RELEASED_I     0x97
#define KEY_RELEASED_J     0xA4
#define KEY_RELEASED_K     0xA5
#define KEY_RELEASED_L     0xA6
#define KEY_RELEASED_M     0xB2
#define KEY_RELEASED_N     0xB1
#define KEY_RELEASED_O     0x98
#define KEY_RELEASED_P     0x99
#define KEY_RELEASED_Q     0x90
#define KEY_RELEASED_R     0x93
#define KEY_RELEASED_S     0x9F
#define KEY_RELEASED_T     0x94
#define KEY_RELEASED_U     0x96
#define KEY_RELEASED_V     0xAF
#define KEY_RELEASED_W     0x91
#define KEY_RELEASED_X     0xAD
#define KEY_RELEASED_Y     0x95
#define KEY_RELEASED_Z     0xAC

#define KEY_RELEASED_MINUS                 0x8C
#define KEY_RELEASED_SEMICOLON             0xA7
#define KEY_RELEASED_COMMA                 0xB3
#define KEY_RELEASED_DOT                   0xB4
#define KEY_RELEASED_SINGLE_QUOTE          0xA8
#define KEY_RELEASED_BACKSLASH             0xAB
#define KEY_RELEASED_SLASH                 0xB5
#define KEY_RELEASED_LSQARE_BRACKET        0x9A
#define KEY_RELEASED_RSQUARE_BRACET        0x9B
#define KEY_RELEASED_EQUALS                0x8D

#define KEY_RELEASED_ESCAPE       0x81
#define KEY_RELEASED_BACKSPACE    0x8E
#define KEY_RELEASED_TAB          0x8F
#define KEY_RELEASED_ENTER        0x9C
#define KEY_RELEASED_LCTRL        0x9D
#define KEY_RELEASED_LSHIFT       0xAA
#define KEY_RELEASED_RSHIFT       0xB6
#define KEY_RELEASED_LALT         0xB8
#define KEY_RELEASED_SPACE        0xB9
#define KEY_RELEASED_CAPS_LOCK    0xBA

#define KEY_RELEASED_F1           0xBB
#define KEY_RELEASED_F2           0xBC
#define KEY_RELEASED_F3           0xBD
#define KEY_RELEASED_F4           0xBE
#define KEY_RELEASED_F5           0xBF
#define KEY_RELEASED_F6           0xC0
#define KEY_RELEASED_F7           0xC1
#define KEY_RELEASED_F8           0xC2
#define KEY_RELEASED_F9           0xC3
#define KEY_RELEASED_F10          0xC4
#define KEY_RELEASED_F11          0xD7
#define KEY_RELEASED_F12          0xD8

#define KEY_RELEASED_NUMLOCK      0xC5
#define KEY_RELEASED_SCROLLLOCK   0xC6

#define UNKNOWN_SCANCODE_CHAR 0x00




void init_keyboard();


#endif /* KEYBOARD_H */
