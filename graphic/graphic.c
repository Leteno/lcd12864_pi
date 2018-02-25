#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphic.h"
#include "../hardware/lcd12864_util.h"
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
#if DEBUG
    printf("map_size: %d\n", map_size);
#endif
    int i;
    for (i = 0; i < map_size; i++) {
	panel->map[i] = 0x0;
    }
}

void canvas_free(struct canvas panel) {
    if (panel.map)
	free(panel.map);
}

void clear_canvas(struct canvas panel) {
    assert(panel.map);
    int map_size = panel.width * panel.height / panel.bitwise;
    int i;
    for (i = 0; i < map_size; i++) {
	panel.map[i] = 0x0;
    }
}

void print_canvas(struct canvas panel) {
    int block_size = panel.width / panel.bitwise;
    int col, row;
    for (row = 0; row < panel.height; row++) {
	for (col = 0; col < block_size; col++) {
	    printf("%X ", panel.map[col + row * block_size]);
	}
	printf("\n");
    }
}

void canvas_copy(struct canvas *source, struct canvas *target) {
    assert(source);
    assert(source->map);
    assert(target);

    target->width = source->width;
    target->height = source->height;
    target->bitwise = source->bitwise;

    int map_size = target->width * target->height / target->bitwise;
    if (!target->map) {
	target->map = (unsigned char *)malloc(map_size * sizeof(char) + 1);
	int i;
	for (i = 0; i < map_size; i++) {
	    target->map[i] = 0x0;
	}
    }
    memcpy(target->map, source->map, map_size);
}

void set_pixel(struct canvas panel, int x, int y, int on) {
    assert(panel.map);
    if (x >= panel.width) x = panel.width - 1;
    if (y >= panel.height) y = panel.height - 1;
    int position = panel.width / panel.bitwise * y + x / panel.bitwise; // frankly speaking, this is wrong when x > 64
    unsigned char position_in_char = 128 >> (x % panel.bitwise);
    if (on > 0) {
	panel.map[position] |= position_in_char; // TODO make it clear
    } else {
	panel.map[position] &= !position_in_char; // TODO make it clear
    }
}

int draw_ascii(struct canvas panel, unsigned char ascii, int x, int y) {
    assert(panel.map);
    if (x >= panel.width || y >= panel.height) {
	return 0;
    }
    struct sprite w = getAsciiWord(ascii);
    draw_sprite(panel, w, x, y);
    int width = w.width;
    sprite_free(w);
    return width;
}

void draw_word(struct canvas panel, unsigned char* ascii_word, int x, int y) {
    assert(panel.map);
    char* p = ascii_word;
    while (*p) {
	int offset = draw_ascii(panel, *p, x, y) + 1;
	assert(offset);
	x += offset;
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

void c_mem_copy(unsigned char* source, unsigned char* target, int sourceStartBit, int targetStartBit, int bitLen) {
    assert(source);
    assert(target);
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

	*target &= clear_at_position(targetStartBit); // reset at first
	if (*source & only_at_position(sourceStartBit)) {
	    *target |= only_at_position(targetStartBit);
	}

#if DEBUG
	printf("source: %X bit_position: %d, target: %X bit_position: %d\n", *source, sourceStartBit, *target, targetStartBit);
#endif
	sourceStartBit++;
	targetStartBit++;
	bitLen--;
    }
}

void draw_sprite(struct canvas panel, struct sprite s, int x, int y) {
    assert(panel.map);
    assert(s.data);
    int h;
    int bit_offset = 0;
    unsigned char *target = panel.map;
    unsigned char *source = s.data;
    int target_position,
	source_position,
	source_start_index,
	xMod8 = x % panel.bitwise,
	col_in_row = panel.width / panel.bitwise,
	target_start_index = x % panel.bitwise;
    int copyBitLen = s.width;
    if (panel.width - x < s.width) {
	copyBitLen = panel.width - x;
    }
#if DEBUG
    int r;
    for (r = 0; r < 7; r++) {
	printf("%x ", s.data[r]);
    }
#endif
    for (h = 0; h < s.height; h++, y++) {
	if (y >= panel.height) break;
	target_position = col_in_row * y + x / panel.bitwise;
	source_position = (s.width * h) / 8;
	source_start_index = (s.width * h) % 8;
	c_mem_copy(source+source_position, target+target_position, source_start_index, target_start_index, copyBitLen);
    }
#if DEBUG
    print_canvas(panel);
#endif
}

void draw_sprite_test(struct canvas panel) {
    assert(panel.map);

    struct sprite w = getAsciiWord('A');
    draw_sprite(panel, w, 0, 0);
    sprite_free(w);
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
    assert(panel.map);
    unsigned char col = 0, row = 0;
    unsigned char *data = panel.map;
    for (row = 0; row < 32; row++) {
	set_graphic_on(1); // it should be 0 but I don't know why 0 causes the image flash every moment
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
