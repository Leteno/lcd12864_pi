#include "cat_game_frame.h"
#include "game_sprite.h"
#include "game_object.h"
#include "map.h"
#include "../../../hardware/switch_util.h"
#include "../../../graphic/graphic.h"

struct game_object bird;
struct game_object fruit;
void game_frame_init(struct canvas panel) {
    game_sprite_init();
    bird.sprite = get_bird();
    bird.x = (panel.width - bird.sprite.width) / 2;
    bird.y = (panel.height - bird.sprite.height) / 2;
    fruit.sprite = get_fruit();
    fruit.x = 0;
    fruit.y = 0;
    map_init(panel);
}

void game_frame_free() {
    game_sprite_free();
}

void game_frame_on_press(int btnType) {
    if (BTN_A & btnType) {
	bird.y += 5;
    }
    if (BTN_B & btnType) {
	bird.y += 10;
    }
}

void valid_game_object(struct game_object* o, struct canvas panel) {
    int half_width = o->sprite.width / 2;
    if (o->x + half_width + 1 > panel.width) {
	o->x = panel.width - half_width;
    }
    if (o->x - half_width - 1 < 0) {
	o->x = half_width + 1;
    }
    int half_height = o->sprite.height / 2;
    if (o->y + half_height + 1 > panel.height) {
	o->y = panel.height - half_height;
    }
    if (o->y - half_height - 1 < 0) {
	o->y = half_height + 1;
    }
}

void draw_game_frame(struct canvas panel) {
    // step one: redraw the frame every time
    // step two: just repaint tiny part, see the efficency
    bird.y -= 1;
    map_moving_forward();
    valid_game_object(&bird, panel);
    draw_map_to_canvas(panel);
    draw_sprite(panel, bird.sprite, bird.x, bird.y);
}
