#include "ascii.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "font8x7.h"
#include "font5x7.h"

struct sprite getAsciiWord_8x7(char ascii) {
    struct sprite w;
    w.width = 8;
    w.height = 7;
    w.data = (unsigned char*) malloc(w.height * w.width / 8 + 1);
    const unsigned char *row;
    int index = ascii - 32; // before 0x20 is none-print-code
    if (index > 32 + 32) {
        row = AsciiFont3[index - 32 - 32];
    } else if (index > 32) {
	row = AsciiFont2[index - 32];
    } else {
	row = AsciiFont1[index];
    }
    char* p = w.data;
    int i;
    for (i = 0; i < w.height; i++) {
	p[i] = row[i];
    }
    return w;
}

struct sprite getAsciiWord_5x7(char ascii) {

    // code before 0x20 is non-print-code
    assert(ascii >= 0x20 && ascii <= 0x7F);

    struct sprite w;
    w.width = 5;
    w.height = 7;
    w.data = (unsigned char*) malloc(w.height * w.width / 8 + 1);

    char* p = w.data;
    char* row = Font5x7;
    row += 5 * (ascii - 0x20);
    int i, size_5x7 = 5;
    for (i = 0; i < size_5x7; i++) {
	p[i] = row[i];
    }
    return w;
}

struct sprite getAsciiWord(char ascii) {
    return getAsciiWord_5x7(ascii);
}

struct sprite getDotDotDot() {
    struct sprite w;
    w.width = 5;
    w.height = 7;
    w.data = (unsigned char*) malloc(w.height * w.width / 8 + 1);
    int i;
    for (i = 0; i < 5; i++) {
	w.data[i] = dot_dot_dot[i];
    }
    return w;
}
