#include "hardware/lcd12864_util.h"
#include "hardware/switch_util.h"
#include "graphic/graphic.h"
#include "graphic/matrix.h"
#include "stdio.h"

#include "config/config.h"

int main(int argc, char** argv) {
    printf("init_env\n");
    init_env();
    printf("clear_graphic_mem\n");
    clear_graphic_mem();
    printf("canvas_init\n");
    struct canvas panel;
    canvas_init(&panel);

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
    return 0;
}
