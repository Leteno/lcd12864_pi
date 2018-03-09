#include "../cat_main_frame.h"
#include "../../../hardware/switch_util.h"
#include "../../../graphic/sprite.h"
#include "../../../graphic/graphic.h"
#include "cat_welcome_frame.h"
#include "frame_128x64.h"

#include <stdlib.h>
#include <string.h>

struct sprite frame_border_sprite;
struct welcome_frame_data data;
void init_welcome_frame() {

    data.title_animationTime = 100;
    data.title_currentTime = 0;

    data.PressCoin_TwinkleTime = 10;
    data.PressCoin_CurrentTime = 0;
    data.show_PressCoin = 0x0;

    data.planeX = 0;
    data.planeY = 56;

    data.enter_NextFrame = 0x0;
    data.AnimationCount_before_EnterNextFrame = 4;
    data.AnimationTime_before_EnterNextFrame = 8;

    // TODO shrink it with function
    frame_border_sprite.width = 128;
    frame_border_sprite.height = 64;
    int data_size = frame_border_sprite.width * frame_border_sprite.height / 8 + 1;
    frame_border_sprite.data = (unsigned char*) malloc(data_size);
    memcpy(frame_border_sprite.data, frame_128x64_border1_matrix, data_size);
}

void free_welcome_frame() {
    if (frame_border_sprite.data) {
	free(frame_border_sprite.data);
    }
}

void welcome_frame_on_press(int btnType) {
    if (BTN_A & btnType || BTN_B & btnType) {
	// TODO add smooth response will be better
	data.enter_NextFrame = 0x1;
	data.CurrentCount_before_EnterNextFrame = 0;
	data.CurrentTime_before_EnterNextFrame = 0;
    }
}

void draw_welcome_frame(struct canvas panel) {
    // White frame
    draw_sprite(panel, frame_border_sprite, 0, 0);

    // Title animation
    if (data.title_currentTime < data.title_animationTime) {
	data.title_currentTime++;
    }
    if (data.title_currentTime > data.title_animationTime / 8) {
	draw_word(panel, "Cator!", 4, 10);
    }
    if (data.title_currentTime > data.title_animationTime * 3 / 8) {
	draw_word(panel, "Go!", 20, 20);
    }
    if (data.title_currentTime > data.title_animationTime / 2) {
	draw_word(panel, "GO!!", 50, 20);
    }
    if (data.title_currentTime > data.title_animationTime * 5 / 8) {
	draw_word(panel, "GO!!", 84, 20);
    }
    if (data.title_currentTime < data.title_animationTime * 3 / 4) {
	return;
    }

    // Animation before going to next frame
    if (data.enter_NextFrame) {
	if (data.CurrentCount_before_EnterNextFrame >= data.AnimationCount_before_EnterNextFrame) {
	    game_next_frame();
	}
	if (data.CurrentTime_before_EnterNextFrame++ >= data.AnimationTime_before_EnterNextFrame) {
	    data.CurrentCount_before_EnterNextFrame++;
	    data.CurrentTime_before_EnterNextFrame = 0;
	} else {
	    draw_word(panel, "PRESS COIN", 20, 40);
	}
	return;
    }

    // Normal Animation
    if (data.show_PressCoin) {
	draw_word(panel, "PRESS COIN", 20, 40);
    }
    if (data.PressCoin_CurrentTime++ >= data.PressCoin_TwinkleTime) {
	data.show_PressCoin = !data.show_PressCoin;
	data.PressCoin_CurrentTime = 0;
    }
}
