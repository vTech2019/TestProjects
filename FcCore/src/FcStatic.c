#include <stdint.h>
#include <stdio.h>

FILE* eFileError = NULL;

#ifdef __linux__
#include <X11/Xlib.h>
Display *FcDisplay = 0;
uint8_t FcInitWindowData = 0;

#endif

