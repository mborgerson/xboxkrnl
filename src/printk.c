#include "boot.h"

int putchar(int c);
int serial_putchar(int c);
int console_putchar(int c);

int printk(const char *szFormat, ...) {  // printk displays to video
	char szBuffer[512*2];
	u16 wLength=0;
	va_list argList;
	va_start(argList, szFormat);
	wLength=(u16) vsprintf(szBuffer, szFormat, argList);
	va_end(argList);

	szBuffer[sizeof(szBuffer)-1]=0;
        if (wLength>(sizeof(szBuffer)-1)) wLength = sizeof(szBuffer)-1;
	szBuffer[wLength]='\0';

	// BootVideoChunkedPrint(szBuffer);

	char *p = szBuffer;
	for (; *p; p++) putchar(*p);

	return wLength;
}

int putchar(int c)
{
	return serial_putchar(c);
	// return console_putchar(c);
}
