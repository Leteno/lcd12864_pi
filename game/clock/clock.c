#include "../../hardware/lcd12864_util.h"
#include "../../hardware/switch_util.h"
#include "../../graphic/graphic.h"
#include "../../widget/label.h"
#include "../../widget/frame.h"

#include "get_weather.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <pthread.h>

struct frame frame;
int game_init();
int game_free();
void* update_weather(void* weather_label);
void* update_pm25(void* pm25_label);
void* show_hit_me(void* hit_me_label);

int main(int argc, char** argv) {

    game_init();

    struct label name = create_label("Bonjour, Mr.zheng", 120, 20, A_CENTER);
    struct label clock = create_label("12:00:00", 80, 10, A_CENTER);
    struct label weather = create_label("", 80, 10, A_RIGHT);
    struct label pm25 = create_label("", 80, 10, A_RIGHT);
    struct label hit_me = create_label("", 48, 13, A_CENTER);

    add_label(frame, name, 0, 0);

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, update_weather, &weather);
    pthread_create(&tid2, NULL, update_pm25, &pm25);
    pthread_create(&tid3, NULL, show_hit_me, &hit_me);

    for (;;) {
	char new_text[120];
	time_t raw_time;
	time(&raw_time);
	struct tm* t = localtime(&raw_time);
	sprintf(new_text, "%02d:%02d:%02d\0", (t->tm_hour + 8) % 24, t->tm_min, t->tm_sec);
	set_label_text(&clock, new_text);
	add_label(frame, clock, 0, 20);

	draw_canvas(frame.canvas);
	usleep(500);
    }

    game_free();
    return 0;
}

void* update_weather(void* weather_label) {
    char max_tmp[10];
    get_max_tmp(max_tmp, 10);
    char min_tmp[10];
    get_min_tmp(min_tmp, 10);

    char result[1024];
    sprintf(result, "%s-%s'C", min_tmp, max_tmp);
    struct label* label = weather_label;
    set_label_text(label, result);
    add_label(frame, *label, 48, 40);
}

void* update_pm25(void* pm25_label) {
    char pm_25[10];
    get_pm25(pm_25, 10);
    char result[1024];
    sprintf(result, "Pm2.5: %03s\0", pm_25);

    struct label* label = pm25_label;
    set_label_text(label, result);
    add_label(frame, *label, 48, 52);
}

void* show_hit_me(void* hit_me_label) {
    struct label* phit_me = hit_me_label;
    int show_hit_me = 0x0;
    while(1) {
	set_label_border(phit_me, show_hit_me, 0);
	set_label_text(phit_me, show_hit_me ? "hit_me": "");
	show_hit_me = !show_hit_me;
	add_label(frame, *phit_me, 6, 50);
	sleep(1);
    }
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
