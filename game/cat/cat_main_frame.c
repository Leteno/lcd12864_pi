#include "cat_main_frame.h"
#include "../../hardware/switch_util.h"
#include "../../graphic/sprite.h"

#include <stdlib.h>

struct cat {
    int x, y;
    struct sprite cat_sprite;
};

struct cat *p_cat;
void game_init() {
    p_cat = (struct cat*) malloc(sizeof(struct cat));
    p_cat->x = 0;
    p_cat->y = 0;
    generateLiu(&(p_cat->cat_sprite));
}

void game_free() {
    if (p_cat) {
	free(p_cat);
	// free sprite?
    }
}

void game_on_press(int btnType) {
    if (BTN_A & btnType) {
	p_cat->x ++;
    }
    if (BTN_B & btnType) {
	p_cat->x --;
    }
}

void game_draw_frame(struct canvas panel) {
    draw_sprite(panel, p_cat->cat_sprite, p_cat->x, p_cat->y);
}
