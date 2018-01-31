#ifndef MATRIX_H
#define MATRIX_H

#include "graphic.h"

struct matrix {
    int index;
    struct canvas *panel;
};

void matrix_init(struct matrix* m);
void matrix_free(struct matrix* m);

void push_matrix(struct matrix* m, struct canvas panel);
void pop_matrix(struct matrix* m, struct canvas *panel);

void matrix_test(struct canvas *panel);
#endif
