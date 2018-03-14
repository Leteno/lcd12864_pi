#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../hardware/lcd12864_util.h"
#include "matrix.h"
#include "graphic.h"

#define FRAME_SIZE_IN_MATRIX 10

void matrix_init(struct matrix* m) {
    m->index = 0;
    m->panel = (struct canvas*) malloc(FRAME_SIZE_IN_MATRIX * sizeof(struct canvas));
    int i;
    for (i = 0; i < FRAME_SIZE_IN_MATRIX; i++) {
	m->panel[i] = canvas_init(LCD_WIDTH, LCD_HEIGHT);
    }
}

void matrix_free(struct matrix* m) {
    assert(m);
    assert(m->panel);
    int i = 0;
    for (i = 0; i < FRAME_SIZE_IN_MATRIX; i++) {
	if (!(m->panel + i)) break;
	canvas_free(m->panel[i]);
    }
    free(m->panel);
}

void push_matrix(struct matrix* m, struct canvas panel) {
    assert(m);
    assert(m->panel);
    assert(panel.map);
    // copy
    canvas_copy(&panel, m->panel + m->index);

    m->index++;
    if (m->index >= FRAME_SIZE_IN_MATRIX) {
	m->index = 0;
    }
}

void pop_matrix(struct matrix* m, struct canvas *panel) {
    assert(m);
    assert(m->panel);
    assert(panel->map);
    // de copy
    m->index--;
    if (m->index < 0) {
	m->index = FRAME_SIZE_IN_MATRIX - 1;
    }

    canvas_copy(m->panel + m->index, panel);
}

void matrix_test(struct canvas *pPanel) {
    struct matrix m;
    matrix_init(&m);
    push_matrix(&m, *pPanel);

    draw_canvas(*pPanel);
    sleep(2);

    clear_canvas(*pPanel);

    draw_canvas(*pPanel);
    sleep(2);

    pop_matrix(&m, pPanel);

    draw_canvas(*pPanel);

    matrix_free(&m);
}
