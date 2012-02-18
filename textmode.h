#ifndef __textmode_h__
#define __textmode_h__

#include "standard.h"

#define COLOR_BLACK     0x00
#define COLOR_BLUE      0x01
#define COLOR_GREEN     0x02
#define COLOR_CYAN      0x03
#define COLOR_RED       0x04
#define COLOR_MAGENTA   0x05
#define COLOR_BROWN     0x06
#define COLOR_LTGRAY    0x07
#define COLOR_DKGRAY    0x08
#define COLOR_LTBLUE    0x09
#define COLOR_LTGREEN   0x0A
#define COLOR_LTCYAN    0x0B
#define COLOR_LTRED     0x0C
#define COLOR_LTMAGENTA 0x0D
#define COLOR_LTBROWN   0x0E
#define COLOR_WHITE     0x0F

#define macro_putch(x, y, ch) screen_memory[(y * 80) + x] = (text_color << 8) | ch

extern void textmode_clear(void);
extern void textmode_settextcolor(unsigned char fore, unsigned char back);
extern void textmode_updatecursor(void);
extern void textmode_scroll(void);
extern void textmode_putch(char ch);
extern int textmode_puts(const char* s);

#endif
