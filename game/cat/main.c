#include "../../hardware/lcd12864_util.h"
#include "../../hardware/switch_util.h"
#include "../../graphic/graphic.h"
#include "../../graphic/matrix.h"
#include "cat_main_frame.h"

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/timeb.h>

#include "../../config/config.h"
void new_logic();
void old_test();

int main(int argc, char** argv) {

    new_logic();
    return 0;
}

void* draw(void* arg) {
    assert(arg);
    struct canvas* panel = arg;
    struct timeb tp;
    ftime(&tp);
    int last_time = tp.time;
    int last_millitm = tp.millitm;
    int T = 1000/60;

    for (;;) {
	ftime(&tp);
	// current_time = {time}.{millitm}, such as 1234.200
	int duration = (tp.time - last_time) * 1000 + (tp.millitm - last_millitm);
	if (duration > T) {
	    // the bottle neck
	    // 32 - 17 = 15 ms to excute this function.
	    draw_canvas(*panel);
	}
    }
}

void new_logic() {
    init_env();
    switch_util_setup();
    clear_graphic_mem();
    struct canvas main_panel = canvas_init(LCD_WIDTH, LCD_HEIGHT);
    struct canvas second_panel = canvas_init(LCD_WIDTH, LCD_HEIGHT);

    pthread_t tid;
    pthread_create(&tid, NULL, draw, &main_panel);

    struct timeb tp;
    ftime(&tp);
    int last_time = tp.time;
    int last_millitm = tp.millitm;
    int T = 1000/24;

    game_init();
    for (;;) {
	ftime(&tp);
	// current_time = {time}.{millitm}, such as 1234.200
	int duration = (tp.time - last_time) * 1000 + (tp.millitm - last_millitm);
	if (duration > T) {
	    // game/cat/cat_main_frame.h
	    game_on_press(getButton());
	    game_process(second_panel);
	    // add mutex
	    canvas_copy(second_panel, &main_panel);

	    printf("duration: %d, fps: %5.2f\n", duration, 1000.0f / duration);
	    last_time = tp.time;
	    last_millitm = tp.millitm;
	}
    }
    game_free();

    canvas_free(main_panel);
    canvas_free(second_panel);
}

void old_test() {
    printf("init_env\n");
    init_env();
    printf("clear_graphic_mem\n");
    clear_graphic_mem();
    printf("canvas_init\n");
    struct canvas panel = canvas_init(LCD_WIDTH, LCD_HEIGHT);

    printf("canvas width %d height %d bitwise %d\n", panel.width, panel.height, panel.bitwise);

    printf("draw_sprite_test\n");
    draw_sprite_test(panel);
    draw_word(panel, "Bonjour", 73, 30);
    draw_word(panel, "Jiang", 83, 42);
    draw_canvas(panel);

    printf("matrix_test\n");
    matrix_test(&panel);

    printf("canvas_free\n");
    canvas_free(panel);

    switch_util_setup();
    switch_util_test();
}
