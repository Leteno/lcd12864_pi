#ifndef FRAME_H
#define FRAME_H

#include "../graphic/canvas.h"
#include "../widget/label.h"

struct frame {
    int width;
    int height;
    struct canvas canvas;
};

struct frame create_frame(int width, int height);

void add_label(struct frame frame, struct label label, int x, int y);

void add_frame(struct frame source, struct frame target, int x, int y);

void free_frame(struct frame frame);

#endif
