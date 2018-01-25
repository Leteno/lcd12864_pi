#include <stdlib.h>
#include <stdio.h>

#include "graphic.h"
#include "../lcd12864_util.h"
#include "../font/ascii.h"


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

void draw_ascii(struct canvas *panel, unsigned char ascii, int x, int y) {
    if (x >= panel->width || y >= panel->height) {
	return;
    }
    unsigned char* data = ascii_init_dot_matrix_buffer();
    int row = getDotMatrixOfAscii(ascii, data), r;
    for (r = 0; r < row; r++) {
	printf("%x ", data[r]);
    }
    printf("\n");
    int start_index = x % panel->bitwise;
    int position, nextPosition;
    int col_in_row = panel->width / panel->bitwise;
    for (r = 0; y < panel->height && r < row; y++, r++) {
	position = col_in_row * y + x / panel->bitwise;
	printf("map[%d] = %d\n", position, panel->map[position]);
	unsigned char source1 = data[r] >> start_index;
	unsigned char mask1 = 0XFF << (panel->bitwise - start_index);
	panel->map[position] &= mask1;
	panel->map[position] |= source1;
	printf("map[%d] = %d\n", position, panel->map[position]);
	nextPosition = position + 1;
	if (!(nextPosition % col_in_row)) continue; // out of bound
	unsigned char source2 = data[r] << (panel->bitwise - start_index);
	unsigned char mask2 = 0xFF >> start_index;
	printf("map[%d] = %d\n", nextPosition, panel->map[nextPosition]);
	panel->map[nextPosition] &= mask2;
	panel->map[nextPosition] |= source2;
	printf("map[%d] = %d\n", nextPosition, panel->map[nextPosition]);
    }
    
    if (data) {
	free(data);
    }
}

void draw_word(struct canvas *panel, unsigned char* ascii_word, int x, int y) {
    int foot = 8;
    char* p = ascii_word;
    while (*p) {
	draw_ascii(panel, *p, x, y);
	x += foot;
	p++;
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
