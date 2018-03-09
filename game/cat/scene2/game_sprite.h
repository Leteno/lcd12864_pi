#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "../../../graphic/sprite.h"
#include "../../../graphic/graphic.h"

struct plane_sprite {
    struct sprite normal;
    struct sprite crash1;
    struct sprite crash2;
    struct sprite crash3;
};

void game_sprite_init();
void game_sprite_free();
void draw_plane(struct canvas panel, int x, int y);

#endif
