#ifndef GRAPHIC_H
#define GRAPHIC_H

struct canvas {
    int width, height, bitwise;
    unsigned char *map;
};

void canvas_init(struct canvas *panel);

void canvas_free(struct canvas *panel);

void set_pixel(struct canvas *panel, int x, int y, int on);

void draw_canvas(struct canvas panel);

#endif
