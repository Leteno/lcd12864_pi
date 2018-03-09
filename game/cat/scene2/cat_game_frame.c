#include "cat_game_frame.h"
#include "../../../hardware/switch_util.h"
#include "../../../graphic/graphic.h"

void game_frame_init() {
}

void game_frame_free() {
}

void game_frame_on_press(int btnType) {
    if (BTN_A & btnType) {
    }
    if (BTN_B & btnType) {
    }
}

void draw_game_frame(struct canvas panel) {
    // step one: redraw the frame every time
    // step two: just repaint tiny part, see the efficency
}
