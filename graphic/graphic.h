#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "sprite.h"

struct canvas {
    int width, height, bitwise;
    unsigned char *map;
};

void canvas_init(struct canvas *panel);

void canvas_free(struct canvas *panel);

void set_pixel(struct canvas *panel, int x, int y, int on);

void draw_ascii(struct canvas *panel, unsigned char ascii, int x, int y);

void draw_word(struct canvas *panel, unsigned char* ascii_word, int x, int y);

void draw_sprite(struct canvas *panel, struct sprite s, int x, int y);

void draw_sprite_test(struct canvas* panel);

void draw_canvas(struct canvas panel);

#endif
