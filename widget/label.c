#include "label.h"
#include "../graphic/canvas.h"
#include "../graphic/graphic.h"

#include <assert.h>
#include <string.h>

struct label create_label(unsigned char* str, int width, int height, int align) {
    struct label label;
    label.width = width;
    label.height = height;
    label.align = align;
    label.data = str;
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
    if (origin_len > strlen(new_text)) {
	clear_canvas(label->canvas);
    }
    draw_word_with_bound(label->canvas, new_text, 0, 0, -1, -1, label->align);
}
