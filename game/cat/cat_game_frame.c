#include "cat_game_frame.h"
#include "../../hardware/switch_util.h"
#include "../../graphic/graphic.h"

int x = 0, y = 10;

void game_frame_init() {
}

void game_frame_free() {
}

void game_frame_on_press(int btnType) {
    if (BTN_A & btnType) {
	x--;
	if (x < 0) {
	    x = 0;
	}
    }
    if (BTN_B & btnType) {
	x++;
	int whatEver = 100;
	if (x > whatEver) {
	    x = whatEver;
	}
    }
}

void draw_game_frame(struct canvas panel) {
    draw_word(panel, "Hi~", x, y);
}
