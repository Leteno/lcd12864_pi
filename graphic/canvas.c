#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "canvas.h"
#include "../utils/math_utils.h"

struct canvas canvas_init(int width, int height) {
    struct canvas panel;
    panel.width = width;
    panel.height = height;
    panel.bitwise = sizeof(unsigned char) * 8;
    int map_size = panel.width * panel.height / panel.bitwise;
    panel.map = (unsigned char *)malloc(map_size * sizeof(char));
#if DEBUG
    printf("map_size: %d\n", map_size);
#endif
    int i;
    for (i = 0; i < map_size; i++) {
	panel.map[i] = 0x0;
    }
    return panel;
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

void canvas_copy(struct canvas source, struct canvas *target) {
    assert(source.map);
    assert(target);

    target->width = source.width;
    target->height = source.height;
    target->bitwise = source.bitwise;

    int map_size = target->width * target->height / target->bitwise;
    if (!target->map) {
	target->map = (unsigned char *)malloc(map_size * sizeof(char) + 1);
	int i;
	for (i = 0; i < map_size; i++) {
	    target->map[i] = 0x0;
	}
    }
    memcpy(target->map, source.map, map_size);
}

// TODO use a better function, this one will cost at least 21 operation per bit
// copy from graphic.c
unsigned char _clear_at_position(int startBit) {
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

unsigned char _only_at_position(int startBit) {
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

void _bit_mem_copy(unsigned char* source, unsigned char* target, int sourceStartBit, int targetStartBit, int bitLen) {
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

	*target &= _clear_at_position(targetStartBit); // reset at first
	if (*source & _only_at_position(sourceStartBit)) {
	    *target |= _only_at_position(targetStartBit);
	}

#if DEBUG
	printf("source: %X bit_position: %d, target: %X bit_position: %d\n", *source, sourceStartBit, *target, targetStartBit);
#endif
	sourceStartBit++;
	targetStartBit++;
	bitLen--;
    }
}

void canvas_copy_bound(struct canvas source, struct point s_from, struct point s_to, struct canvas* target, struct point t_from, char is_infinit) {
    assert(source.map);
    assert(target);
    assert(target->map);

    // TODO s_from should be smaller than s_to

    int s_rows = s_to.y - s_from.y;
    int s_columns = s_to.x - s_from.x;
    int r;
    for (r = 0; r < s_rows; r++) {
	int t_row = (t_from.y + r) % target->height; // TODO
	int left = s_to.x - s_from.x;
	int t_from_x = t_from.x;
	while (left > 0) {
	    int copy_bit_len = MIN(left, target->width - t_from_x);
	    int t_p = t_from.x + (t_from.y + r) * target->width;
	    int s_p = s_from.x + (s_from.y + r) * source.width;
	    _bit_mem_copy(
		source.map + s_p / 8,
		target->map + t_p / 8,
		s_p % 8,
		t_p % 8,
		copy_bit_len);
	    if (!is_infinit) {
		break;
	    }
	    left -= copy_bit_len;
	    t_from_x = 0;
	}
    }
}

