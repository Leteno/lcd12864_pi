#include "cat_game_frame.h"
#include "game_sprite.h"
#include "game_object.h"
#include "map.h"
#include "../../../hardware/switch_util.h"
#include "../../../graphic/graphic.h"

#include <sys/timeb.h>

struct game_object bird;
struct game_object fruit;

struct timeb first_time;
struct timeb last_time;

void game_frame_init(struct canvas panel) {
    game_sprite_init();
    bird.sprite = get_bird();
    bird.x = (panel.width - bird.sprite.width) / 2;
    bird.y = (panel.height - bird.sprite.height) / 2;
    fruit.sprite = get_fruit();
    fruit.x = 0;
    fruit.y = 0;
    map_init(panel);
    ftime(&first_time);
    last_time = first_time;
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

void game_frame_logic_process() {
    // step one: redraw the frame every time
    // step two: just repaint tiny part, see the efficency
    struct timeb current_time;
    ftime(&current_time);
    int elapse0 = (current_time.time - first_time.time) * 1000 + (current_time.millitm - first_time.millitm);
    int elapse1 = (current_time.time - last_time.time) * 1000 + (current_time.millitm - last_time.millitm);

    bird.y -= (int)(elapse1 * 0.06);
    map_moving_forward(elapse0);
}

void draw_game_frame(struct canvas panel) {
    valid_game_object(&bird, panel);
    draw_map_to_canvas(panel);
    draw_sprite(panel, bird.sprite, bird.x, bird.y);
}
