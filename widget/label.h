#ifndef LABEL_H
#define LABEL_H

#include "../graphic/canvas.h"

struct label {
    int width;
    int height;
    int align;
    char* data;
    struct canvas canvas;
};

struct label create_label(unsigned char* str, int width, int height, int align);

void set_label_text(struct label* label, char* new_text);

#endif
