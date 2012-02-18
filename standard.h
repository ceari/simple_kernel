#ifndef __standard_h__
#define __standard_h__

extern void memsetw(unsigned short* dst, char c, int count);
extern void memcpyw(unsigned short* dst, unsigned short* src, int count);
extern void outportb(short port, char b);

#endif
