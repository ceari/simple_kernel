#include "standard.h"

void memsetw(unsigned short* dst, char c, int count) {
    for (int i = 0; i < count; i++) {
        *(dst + i) = c;
    }
}

void memcpyw(unsigned short* dst, unsigned short* src, int count) {
    for (int i = 0; i < count; i++) {
        *(dst + i) = *(src + i);
    }
}

void outportb(short port, char b) {
    __asm("mov %0, %%dx;"::"r"(port));
    __asm("movb %0, %%al;"::"r"(b));
    __asm("out %al, %dx");
}

