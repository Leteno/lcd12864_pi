#include "label.h"
#include "../graphic/canvas.h"
#include "../graphic/graphic.h"

#include <assert.h>
#include <string.h>

void draw_label_border(struct label label);
struct label create_label(unsigned char* str, int width, int height, int align) {
    struct label label;
    label.width = width;
    label.height = height;
    label.align = align;
    label.data = str;
    label.border_on = 0x0;
    label.canvas = canvas_init(width, height);
    draw_word_with_bound(label.canvas, str, 0, 0, -1, -1, align);
    return label;
}

void set_label_text(struct label* label, char* new_text) {
    assert(label);
    if (!new_text) {
	new_text = "";
    }
    int origin_len = 0;
    if (label->data) {
	origin_len = strlen(label->data);
    }
    label->data = new_text;
    clear_canvas(label->canvas);

    draw_word_with_bound(label->canvas, new_text, 0, 0, -1, -1, label->align);
    draw_label_border(*label); // BUGGY may modify words bound if it is too small
}

void draw_label_border(struct label label) {
    if (label.border_on) {
	draw_straight_line(label.canvas, 0, 0, label.width, 0); // TOP
	draw_straight_line(label.canvas, 0, 0, 0, label.height); // LEFT
	draw_straight_line(label.canvas, label.width, 0, label.width, label.height); // RIGHT
	draw_straight_line(label.canvas, 0, label.height, label.width, label.height); // BOTTOM
    }
}


void set_label_border(struct label* label, int on, int repaint) {
    label->border_on = on;
    if (repaint) {
	draw_label_border(*label);
    }
}
