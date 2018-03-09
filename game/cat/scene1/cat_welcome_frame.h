#ifndef CAT_WELCOME_FRAME_H
#define CAT_WELCOME_FRAME_H

#include "../../../graphic/graphic.h"

struct welcome_frame_data {

    int title_animationTime;
    int title_currentTime;

    int PressCoin_TwinkleTime;
    int PressCoin_CurrentTime;
    char show_PressCoin;

    int planeX;
    int planeY;

    // TODO naming, so ugly
    char enter_NextFrame;
    int AnimationCount_before_EnterNextFrame;
    int CurrentCount_before_EnterNextFrame;
    int AnimationTime_before_EnterNextFrame;
    int CurrentTime_before_EnterNextFrame;
};

void init_welcome_frame();
void free_welcome_frame();
void welcome_frame_on_press(int btnType);
void draw_welcome_frame(struct canvas panel);

#endif
