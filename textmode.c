#include "standard.h"
#include "textmode.h"

static unsigned short* screen_memory = (unsigned short *)0xB8000;
static unsigned char   text_color  = (COLOR_BLACK << 4) | COLOR_WHITE;
static char cursor_xpos = 0, cursor_ypos = 0;

void textmode_clear() {
    memsetw(screen_memory, (text_color << 8) | ' ', 80 * 25);
}

void textmode_settextcolor(unsigned char fore, unsigned char back) {
    text_color = ((back & 0x0F) << 4) | (fore & 0x0F);
}

void textmode_updatecursor() {
    static unsigned char xpos_store = 0;
    static unsigned char ypos_store = 0;

    if((xpos_store != cursor_xpos) || (ypos_store != cursor_ypos)) {
        unsigned int temp = (cursor_ypos * 80) + cursor_xpos;
        outportb(0x3D4, 14);
        outportb(0x3D5, temp >> 8);
        outportb(0x3D4, 15);
        outportb(0x3D5, temp);
        ypos_store = cursor_ypos;
        xpos_store = cursor_xpos;
    }
}

void textmode_scroll(void) {
    if(cursor_ypos >= 25) {
        unsigned int temp = cursor_ypos - 24;
        memcpyw(screen_memory, screen_memory + (temp * 80), (25 - temp) * 80);
        memsetw(screen_memory + (25 - temp) * 80, (text_color << 8) | ' ', 80);
        cursor_ypos = 24;
    }
}

void textmode_putch(char ch) {
    switch(ch) {
        case '\b':
            if(!cursor_xpos) {
                if(cursor_ypos) {
                    cursor_xpos = 79;
                    macro_putch(cursor_xpos, --cursor_ypos, ' ');
                }
            }else {
                macro_putch(--cursor_xpos, cursor_ypos, ' ');
            }
            break;
        case '\n':
            cursor_ypos++;
            cursor_xpos = 0;
            break;
        case '\r':
            cursor_xpos = 0;
            break;
        case '\t':
            cursor_xpos = (cursor_xpos + 8) & ~(8 - 1); // method from Brans Kernel Development Tutorial
            break;
        default:
            if(ch >= ' ') {
                macro_putch(cursor_xpos, cursor_ypos, ch);
                cursor_xpos++;
                if(cursor_xpos >= 80) {
                    cursor_xpos = 0;
                    cursor_ypos++;
                }
            }
            break;
    }

    textmode_scroll();
    textmode_updatecursor();
}

int textmode_puts(const char* s) {
    int ticks = 1;
    while(*s) {
        textmode_putch(*(s++));
        ticks++;
    }
    textmode_putch('\n');

    return ticks;
}
