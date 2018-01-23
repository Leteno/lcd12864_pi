#include <stdlib.h>
#include <stdio.h>

#include "graphic.h"
#include "lcd12864_util.h"

#define CANVAS_WIDTH 128
#define CANVAS_HEIGHT 64

void canvas_init(struct canvas *panel) {
    // TODO assert panel
    panel->width = CANVAS_WIDTH;
    panel->height = CANVAS_HEIGHT;
    panel->bitwise = sizeof(unsigned char) * 8;
    int map_size = panel->width * panel->height / panel->bitwise;
    panel->map = (unsigned char *)malloc(map_size * sizeof(char));
    printf("map_size: %d\n", map_size);
    int i;
    for (i = 0; i < map_size; i++) {
	panel->map[i] = 0x0;
    }
}

void canvas_free(struct canvas *panel) {
    if (*(panel->map))
	free(panel->map);
}

void set_pixel(struct canvas *panel, int x, int y, int on) {
    if (x >= panel->width) x = panel->width - 1;
    if (y >= panel->height) y = panel->height - 1;
    int position = panel->width / panel->bitwise * y + x / panel->bitwise; // frankly speaking, this is wrong when x > 64
    unsigned char position_in_char = 128 >> (x % panel->bitwise);
    if (on > 0) {
	panel->map[position] |= position_in_char; // TODO make it clear
    } else {
	panel->map[position] &= !position_in_char; // TODO make it clear
    }
}

/**

 in lcd12864:
 ################ * 32

 in my data:
 ######## * 64

 the line 33 in {my_data} is
 line 1, the right side in {lcd12864}
 */

void draw_canvas(struct canvas panel) {
    unsigned char col = 0, row = 0;
    unsigned char *data = panel.map;
    for (row = 0; row < 32; row++) {
	set_graphic_on(0);
	set_gdram_address(row, 0x0);
	for (col = 0; col < 16; col++) {
	    write_on_ram(data[row * 16 + col]);
	}
	for (col = 0; col < 16; col++) {
	    write_on_ram(data[(row + 32) * 16 + col]);
	}
	set_graphic_on(1);
    }
}

