#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "canvas.h"

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
