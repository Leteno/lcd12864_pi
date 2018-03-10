#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sprite.h"
#include "sprite_matrix.h"

void generateLiu(struct sprite* s) {
//    s->width = 73;
//    s->height = 73;
//    int data_size = s->width * s->height / 8 + 1;
//    s->data = (unsigned char*) malloc(data_size * sizeof(unsigned char));
//    memcpy(s->data, bit_matrix_liu, data_size);

    s->width = 72;
    s->height = 72;
    int data_size = s->width * s->height / 8 + 1;
    s->data = (unsigned char*) malloc(data_size *sizeof(unsigned char));
    memcpy(s->data, yinghuozhishen, data_size);
}

void sprite_init(struct sprite* s, int width, int height, unsigned char *data) {
    assert(s);
    assert(data);
    s->width = width;
    s->height = height;
    int data_size = width * height / 8 + 1;
    s->data = (unsigned char*) malloc(data_size);
    assert(s->data);
    memcpy(s->data, data, data_size);
}

struct sprite get_rectangle_sprite(int width, int height) {
    struct sprite s;
    s.width = width;
    s.height = height;
    int data_size = width * height / 8 + 1;
    s.data = (unsigned char*) malloc(data_size);
    assert(s.data);
    int i;
    for (i = 0; i < data_size; i++) {
	s.data[i] = 0xFF;
    }
    return s;
}

void sprite_free(struct sprite s) {
    if (s.data)
	free(s.data);
}
