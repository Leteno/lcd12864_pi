#include "cat_main_frame.h"
#include "scene1/cat_welcome_frame.h"
#include "scene2/cat_game_frame.h"
#include "../../graphic/sprite.h"

#include <stdlib.h>

struct game_state m_state;

void game_init() {

    m_state.state = welcome;
    m_state.inited = 0x0;
}

void game_free() {
}

void game_on_press(int btnType) {
    switch(m_state.state) {
    case welcome:
	welcome_frame_on_press(btnType);
	break;
    case frame_one:
	game_frame_on_press(btnType);
	break;
    }
}

void game_draw_frame(struct canvas panel) {
    switch(m_state.state) {
    case welcome:
	if (!m_state.inited) {
	    init_welcome_frame();
	    m_state.inited = 0x1;
	}
	draw_welcome_frame(panel);
	break;
    case frame_one:
	if (!m_state.inited) {
	    game_frame_init();
	    m_state.inited = 0x1;
	}
	draw_game_frame(panel);
	break;
    }
}

void game_next_frame() {
    switch(m_state.state) {
    case welcome:
	m_state.state = frame_one;
	m_state.inited = 0x0;
	break;
    case frame_one:
	break;
    }
}
