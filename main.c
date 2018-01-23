#include "lcd12864_util.h"
#include "graphic.h"
#include "stdio.h"
  #include <wiringPi.h>

int main(int argc, char** argv) {
    printf("init_env\n");
    init_env();
    printf("clear_graphic_mem\n");
    clear_graphic_mem();
    printf("canvas_init\n");
    struct canvas panel;
    canvas_init(&panel);

    printf("canvas width %d height %d bitwise %d\n", panel.width, panel.height, panel.bitwise);

    printf("set_pixel\n");

    int i, j = 125;
    for (j = 0; j < 64; j++) {
	for (i = 0; i < 128; i++) {
	    set_pixel(&panel, i, j, i > j);
	}
    }

    printf("draw_canvas\n");
    draw_canvas(panel);

    printf("canvas_free\n");
    canvas_free(&panel);
    return 0;
}
