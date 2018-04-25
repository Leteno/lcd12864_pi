#ifndef CANVAS_H
#define CANVAS_H

struct canvas {
    int width, height, bitwise;
    unsigned char *map;
};

struct point {
    int x, y;
};

struct canvas canvas_init(int width, int height);

void canvas_free(struct canvas panel);

void clear_canvas(struct canvas panel);

void print_canvas(struct canvas panel);

void canvas_copy_bound(struct canvas source, struct point s_from, struct point s_to, struct canvas target, struct point t_from, char is_infinit);

void canvas_copy(struct canvas source, struct canvas *target);

#endif
