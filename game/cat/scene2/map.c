#include "map.h"
#include "../../../graphic/graphic.h"
#include "../../../graphic/sprite.h"

#define RECT_SUM 10

struct canvas map_canvas;
int offset = 0;

struct sprite rects[RECT_SUM];

void map_init(struct canvas canvas) {
    map_canvas = canvas_init(canvas.width * 2, canvas.height);
    int w = canvas.width / RECT_SUM * 3 / 10;
    int i;
    for (i = 0; i < RECT_SUM; i++) {
	rects[i] = get_rectangle_sprite(w, map_canvas.height * (i + 1) / RECT_SUM);
    }
    for (i = 0; i < RECT_SUM; i++) {
	draw_sprite(map_canvas, rects[i], map_canvas.width * i / RECT_SUM, 0);
    }
}

void map_moving_forward() {
    offset += 5;
    if (offset > map_canvas.width) {
	offset -= map_canvas.width;
    }
}

void draw_map_to_canvas(struct canvas canvas) {
    struct point s_from = {
	.x = offset,
	.y = 0
    };
    struct point s_to = {
	.x = offset + canvas.width,
	.y = canvas.height
    };
    struct point t_from = {
	.x = 0,
	.y = 0
    };
    canvas_copy_bound(
	map_canvas,
	s_from,
	s_to,
	&canvas,
	t_from,
	0x0
	);
}
