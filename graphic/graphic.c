#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphic.h"
#include "../utils/math_utils.h"
#include "../hardware/lcd12864_util.h"
#include "../font/ascii.h"

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

void draw_word(struct canvas panel, unsigned char* ascii_word, int x, int y) {
    draw_word_with_bound(panel, ascii_word, x, y, -1, -1, A_LEFT);
}

void draw_word_with_bound(struct canvas panel, unsigned char* ascii_word, int x, int y, int maxX, int maxY, int align) {
    // TODO maybe we could make assert in a function like assert_panel(struct panel)
    assert(panel.map);
    maxX = maxX < 0 ? panel.width - 1 : maxX;
    maxY = maxY < 0 ? panel.height - 1 : maxY;


    int font_width = 5, font_height = 7, width_gap = 1, height_gap = 1;
    int len = strlen(ascii_word);
    { // calculation for alignment
	int area_width = maxX - x;
	int area_height = maxY - y;

	int w = len * (font_width + width_gap);
	int posible_lines = w / area_width + 1;
	int left_width = w > area_width ? 0 : area_width - w;
	int left_height = area_height - posible_lines * (font_height + height_gap);
	if (left_height < 0) left_height = 0;

	if (align & A_LEFT) {
	} else if (align & A_RIGHT) {
	    x = x + left_width;
	} else if (align & A_CENTER) {
	    x = x + left_width / 2;
	}

	if (align & A_TOP) {
	} else if (align & A_BOTTOM) {
	    y = y + left_height;
	} else if (align & A_CENTER) {
	    y = y + left_height / 2;
	}
    }
    int fromX = x;
    
    // Well, to a good answer from a question, you should begin with a bad answer --- Pa.Zheng
    int last_font_width = font_width;
    int last_font_height = font_height;

    char* p = ascii_word;
    int word_len = strlen(p);
    while (*p) {
	if (x + last_font_width >= maxX) {
	    if (y + last_font_height > maxY) {
		// warning it is going to explode
		// draw a dot dot dot
		struct sprite w = getDotDotDot();
		draw_sprite_with_bound(panel, w, x, y, maxX, maxY, align);
		sprite_free(w);
		break;
	    }
	}
	if (x + last_font_width > maxX) {
	    x = fromX;
	    y += last_font_height + height_gap;
	}
	if (y > maxY) {
	    // Like an old Chinese saying: not force to back sky
	    break;
	}
	// TODO generate again and again, reduce it.
	struct sprite w = getAsciiWord(*p);
	draw_sprite_with_bound(panel, w, x, y, maxX, maxY, align);
	x += w.width + width_gap;
	last_font_width = w.width;
	last_font_height = w.height;
	p++;
	sprite_free(w);
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

void bit_mem_copy(unsigned char* source, unsigned char* target, int sourceStartBit, int targetStartBit, int bitLen) {
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
    draw_sprite_with_bound(panel, s, x, y, -1, -1, A_LEFT);
}

void draw_sprite_with_bound(struct canvas panel, struct sprite s, int x, int y, int maxX, int maxY, int align) {
    assert(panel.map);
    assert(s.data);
    maxX = maxX < 0 ? panel.width - 1 : maxX;
    maxY = maxY < 0 ? panel.height - 1 : maxY;
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
    int copyBitLen = s.width; // copy at most in one line
    if (maxX - x < s.width) {
	copyBitLen = maxX - x;
    }
#if DEBUG
    int r;
    for (r = 0; r < 7; r++) {
	printf("%x ", s.data[r]);
    }
#endif
    for (h = 0; h < s.height; h++, y++) {
	if (y > maxY) break;
	target_position = col_in_row * y + x / panel.bitwise;
	source_position = (s.width * h) / 8;
	source_start_index = (s.width * h) % 8;
	bit_mem_copy(source+source_position, target+target_position, source_start_index, target_start_index, copyBitLen);
    }
#if DEBUG
    print_canvas(panel);
#endif
}

void draw_straight_line(struct canvas panel, int startX, int startY, int endX, int endY) {
    int x, y;
    for (x = startX; x <= endX; x++) {
	for (y = startY; y <= endY; y++) {
	    set_pixel(panel, x, y, 1); // actually we can improve it, by copy in bytes not bits
	}
    }
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
