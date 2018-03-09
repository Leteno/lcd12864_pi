#ifndef CAT_GAME_FRAME_H
#define CAT_GAME_FRAME_H

#include "../../../graphic/graphic.h"

struct game_frame_data {
    
};

void game_frame_init();
void game_frame_free();
void game_frame_on_press(int btnType);
void draw_game_frame(struct canvas panel);

#endif
