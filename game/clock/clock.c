#include "../../hardware/lcd12864_util.h"
#include "../../hardware/switch_util.h"
#include "../../graphic/graphic.h"
#include "../../widget/label.h"
#include "../../widget/frame.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct frame frame;
int game_init();
int game_free();

int main(int argc, char** argv) {

    game_init();

    struct label name = create_label("Bonjour, Mr.zheng", 120, 20, A_CENTER);
    struct label clock = create_label("12:00:00", 80, 30, A_CENTER);

    add_label(frame, name, 0, 0);

    for (;;) {
	char new_text[120];
	time_t raw_time;
	time(&raw_time);
	struct tm* t = localtime(&raw_time);
	sprintf(new_text, "%02d:%02d:%02d\0", (t->tm_hour + 8) % 24, t->tm_min, t->tm_sec);
	set_label_text(&clock, new_text);
	add_label(frame, clock, 20, 20);
	draw_canvas(frame.canvas);
	usleep(500);
    }

    game_free();
    return 0;
}

int game_init() {
    init_env();
    clear_graphic_mem();
    frame = create_frame(LCD_WIDTH, LCD_HEIGHT);

    return 0;
}

int game_free() {
    free_frame(frame);
    return 0;
}
