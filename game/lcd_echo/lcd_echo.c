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

    for (int i = 1; i < argc; i++) {
	if (i * 9 > panel.height) break;
//	draw_word_with_bound(panel, argv[i], 0, i * 9, 100, 100, LEFT);
	draw_word(panel, argv[i], 0, i * 9);
    }
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
