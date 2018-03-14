#include "../../hardware/lcd12864_util.h"
#include "../../hardware/switch_util.h"
#include "../../graphic/graphic.h"
#include "../../graphic/matrix.h"

#include <stdio.h>
#include <sys/timeb.h>

#include "../../config/config.h"
void new_logic();
void old_test();

int game_process(struct canvas panel);
int main(int argc, char** argv) {

    init_env();
    switch_util_setup();
    clear_graphic_mem();
    struct canvas panel = canvas_init(LCD_WIDTH, LCD_HEIGHT);

    struct timeb tp;
    ftime(&tp);
    int last_time = tp.time;
    int last_millitm = tp.millitm;
    int T = 1000/60;

    for (;;) {
	ftime(&tp);
	// current_time = {time}.{millitm}, such as 1234.200
	clear_canvas(panel);
	int duration = (tp.time - last_time) * 1000 + (tp.millitm - last_millitm);
	if (duration > T) {
	    // game/cat/cat_main_frame.h
	    game_process(panel);
	    printf("duration: %d, time: %d.%d\n", duration, tp.time, tp.millitm);
	    /*
	    last_millitm = last_millitm + T;
	    if (last_millitm >= 1000) {
		last_millitm -= 1000;
		last_time += 1;
		}
	    */
	    last_time = tp.time;
	    last_millitm = tp.millitm;
	}
	draw_canvas(panel);
    }
    canvas_free(panel);
    return 0;
}

int x = 0;
int game_process(struct canvas panel) {
    draw_word(panel, "ABC", x++, 10);
}
