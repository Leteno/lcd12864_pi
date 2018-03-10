#ifndef SPRITE_H
#define SPRITE_H

struct sprite {
    int width; // in pixel.
    int height; // in pixel.
    unsigned char *data;
};

void generateLiu(struct sprite* s);

void sprite_init(struct sprite* s, int width, int height, unsigned char *data);

void sprite_free(struct sprite s);

#endif
