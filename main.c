#include "lcd12864_util.h"
#include "graphic/graphic.h"
#include "stdio.h"

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

    draw_sprite_test(panel);
    draw_word(panel, "Bonjour", 73, 30);
    draw_word(panel, "Jiang", 83, 42);

    printf("draw_canvas\n");
    draw_canvas(panel);

    printf("canvas_free\n");
    canvas_free(&panel);
    return 0;
}
