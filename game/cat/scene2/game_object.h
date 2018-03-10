#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "../../../graphic/graphic.h"

struct game_object {
    struct sprite sprite;
    int x, y;
};

#endif
