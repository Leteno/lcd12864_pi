#ifndef CAT_WELCOME_FRAME_H
#define CAT_WELCOME_FRAME_H

#include "../../graphic/graphic.h"

void init_welcome_frame();
void free_welcome_frame();
void welcome_frame_on_press(int btnType);
void draw_welcome_frame(struct canvas panel);

#endif
