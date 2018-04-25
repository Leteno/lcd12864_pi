#include "../../hardware/lcd12864_util.h"
#include "../../hardware/switch_util.h"
#include "../../graphic/graphic.h"
#include "../../graphic/matrix.h"

struct canvas panel;
int game_init();
int game_free();

int main(int argc, char** argv) {

    game_init();

    if (argc == 1) {
	draw_word(panel, "no argument", 0, 0);
	draw_canvas(panel);
	game_free();
	return 1;
    }

    draw_word_with_bound(panel, argv[1], 0, 0, -1, -1, A_CENTER | A_RIGHT);

    draw_canvas(panel);

    game_free();
    return 0;
}

int game_init() {
    init_env();
    clear_graphic_mem();
    panel = canvas_init(LCD_WIDTH, LCD_HEIGHT);

    return 0;
}

int game_free() {
    canvas_free(panel);

    return 0;
}
