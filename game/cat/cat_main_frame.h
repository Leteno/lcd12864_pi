#ifndef CAT_MAIN_FRAME_H
#define CAT_MAIN_FRAME_H

#include "../../graphic/graphic.h"

enum frame_state {
    welcome = 0,
    frame_one = 1
};

struct game_state {
    enum frame_state state;
    char inited;
};

void game_init();
void game_free();

void game_on_press(int btnType);

void game_draw_frame(struct canvas panel);

void game_next_frame();

#endif
