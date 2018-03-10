#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "../../../graphic/sprite.h"
#include "../../../graphic/graphic.h"

void game_sprite_init();
void game_sprite_free();
struct sprite get_bird();
struct sprite get_fruit();

#endif
