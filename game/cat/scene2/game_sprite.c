#include "game_sprite.h"

#include "../../../graphic/sprite.h"
#include "../../../graphic/graphic.h"

#include <string.h>
#include <stdlib.h>

struct plane_sprite plane;
/*
struct plane_sprite {
    struct sprite normal;
    struct sprite crash1;
    struct sprite crash2;
    struct sprite crash3;
};
struct sprite {
    int width; // in pixel.
    int height; // in pixel.
    unsigned char *data;
};
*/

void game_sprite_init() {
    unsigned char plane_normal_data[] = {
	0xCF,0x0,0x0
    };
    plane.normal.width = 3;
    plane.normal.height = 3;
    int data_size = plane.normal.width * plane.normal.height / 8 + 1;
    plane.normal.data = (unsigned char*)malloc(data_size);
    memcpy(plane.normal.data, plane_normal_data, data_size);
}

void game_sprite_free() {
    sprite_free(plane.normal);
}
void draw_plane(struct canvas panel, int x, int y) {
    draw_sprite(panel, plane.normal, x, y);
}

