#ifndef CANVAS_H
#define CANVAS_H

struct canvas {
    int width, height, bitwise;
    unsigned char *map;
};

void canvas_init(struct canvas *panel);

void canvas_free(struct canvas panel);

void clear_canvas(struct canvas panel);

void print_canvas(struct canvas panel);

void canvas_copy(struct canvas *source, struct canvas *target);

#endif
