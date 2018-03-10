#include "game_sprite.h"

#include "../../../graphic/sprite.h"
#include "../../../graphic/graphic.h"

#include <string.h>
#include <stdlib.h>

struct sprite bird;
struct sprite fruit;

void bird_init() {
    unsigned char bird_data[] = {
	0x0C, 0x4A, 0x7F, 0x90, 0x18, 0x00,
	0x00 // addition
    };
    int width = 8, height = 5;
    sprite_init(&bird, width, height, bird_data); 
}

void fruit_init() {
    unsigned char fruit_data[] = {
	0x8A, 0xBE, 0xE2, 0x00,
	0x00 // addition
    };
    int width = 5, height = 5;
    sprite_init(&fruit, width, height, fruit_data);
}

void game_sprite_init() {
    bird_init();
    fruit_init();
}

void game_sprite_free() {
    sprite_free(bird);
    sprite_free(fruit);
}
struct sprite get_bird() {
    if (!bird.data)
	bird_init();
    return bird;
}

struct sprite get_fruit() {
    if (!fruit.data)
	fruit_init();
    return fruit;
}
