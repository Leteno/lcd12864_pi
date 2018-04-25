#include "frame.h"
#include "label.h"
#include "../graphic/canvas.h"

struct frame create_frame(int width, int height) {
    struct frame frame;
    frame.width = width;
    frame.height = height;
    frame.canvas = canvas_init(width, height);
    return frame;
}

void add_label(struct frame frame, struct label label, int x, int y) {

    struct point s_from = {0, 0}, s_to = {label.width, label.height}, t_from = {x, y};
    canvas_copy_bound(label.canvas, s_from, s_to, frame.canvas, t_from, 0x0);
}

void add_frame(struct frame target, struct frame source, int x, int y) {
    struct point s_from = {0, 0}, s_to = {source.width, source.height}, to_from = {x, y};
    canvas_copy_bound(source.canvas, s_from, s_to, target.canvas, to_from, 0x0);
}

void free_frame(struct frame frame) {
    canvas_free(frame.canvas);
}
