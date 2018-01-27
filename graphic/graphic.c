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
    if (panel->map)
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

unsigned char clear_at_position(int startBit) {
    // start from left
    switch (startBit) {
    case 0:
	return 0x7F;
    case 1:
	return 0xBF;
    case 2:
	return 0xDF;
    case 3:
	return 0xEF;
    case 4:
	return 0xF7;
    case 5:
	return 0xFB;
    case 6:
	return 0xFD;
    case 7:
	return 0xFE;
    default:
	return 0;
    }
}

unsigned char only_at_position(int startBit) {
    switch (startBit) {
    case 0:
	return 0x80;
    case 1:
	return 0x40;
    case 2:
	return 0x20;
    case 3:
	return 0x10;
    case 4:
	return 0x08;
    case 5:
	return 0x04;
    case 6:
	return 0x02;
    case 7:
	return 0x01;
    default:
	return 0;
    }
}

void mem_copy(unsigned char* source, unsigned char* target, int sourceStartBit, int targetStartBit, int bitLen) {
    // bitlen is 128 at most, so it is ok to copy by bit
    while (bitLen > 0) {
	if (sourceStartBit >= 8) {
	    sourceStartBit %= 8;
	    source++;
	}
	if (targetStartBit >= 8) {
	    targetStartBit %= 8;
	    target++;
	}
	printf("source: %X bit: %d, target: %X bit: %d\n", *source, sourceStartBit, *target, targetStartBit);

	*target &= clear_at_position(targetStartBit); // reset at first
	if (*source & only_at_position(sourceStartBit)) {
	    *target |= only_at_position(targetStartBit);
	}
	    
	sourceStartBit++;
	targetStartBit++;
	bitLen--;
    }
}

void draw_sprite(struct canvas *panel, struct sprite s, int x, int y) { // TODO: use canvas instead of canvas*
    int h;
    int bit_offset = 0;
    unsigned char *target = panel->map;
    unsigned char *source = s.data;
    int target_position,
	source_position,
	source_start_index,
	xMod8 = x % panel->bitwise,
	col_in_row = panel->width / panel->bitwise,
	target_start_index = x % panel->bitwise;
    int copyBitLen = s.width;
    if (panel->width - x < s.width) {
	copyBitLen = panel->width - x;
    }
    int r;
    for (r = 0; r < 7; r++) {
	printf("%x ", s.data[r]);
    }
    for (h = 0; h < s.height; h++, y++) {
	if (y >= panel->height) break;
	target_position = col_in_row * y + x / panel->bitwise;
	source_position = (s.width * h) / 8;
	source_start_index = (s.width * h) % 8;
	mem_copy(source+source_position, target+target_position, source_start_index, target_start_index, copyBitLen);
    }
}

void draw_sprite_test(struct canvas* panel) {
    struct sprite s;
    s.data = ascii_init_dot_matrix_buffer();
    int row = getDotMatrixOfAscii('A', s.data);
    s.width = 8; // buggy
    s.height = row;
//    draw_sprite(panel, s, 0, 0);
    if(s.data) {
	free(s.data);
    }

    generateLiu(&s);
    draw_sprite(panel, s, 0, 0);
    if (s.data) {
	free(s.data);
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
