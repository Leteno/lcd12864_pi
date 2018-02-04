#ifndef CAT_MAIN_FRAME_H
#define CAT_MAIN_FRAME_H

#include "../../graphic/graphic.h"

void game_init();
void game_free();

void game_on_press(int btnType);

void game_draw_frame(struct canvas panel);

#endif
