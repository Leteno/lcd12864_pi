#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "canvas.h"
#include "sprite.h"

// TODO full fill it. Actually, it may be useless in this project, so leave it alone until I have time. Sorry
enum align {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

void set_pixel(struct canvas panel, int x, int y, int on);

void draw_word(struct canvas panel, unsigned char* ascii_word, int x, int y);

void draw_word_with_bound(struct canvas panel, unsigned char* ascii_word, int x, int y, int maxX, int maxY, enum align a);

void draw_sprite(struct canvas panel, struct sprite s, int x, int y);

void draw_sprite_with_bound(struct canvas panel, struct sprite s, int x, int y, int maxX, int maxY, enum align a);

void draw_sprite_test(struct canvas panel);

void draw_canvas(struct canvas panel);

#endif
