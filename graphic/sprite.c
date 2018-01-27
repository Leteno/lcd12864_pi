#include "stdlib.h"
#include "string.h"

#include "sprite.h"

unsigned char bit_matrix_liu[] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1C,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x31,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x20,0x30,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x14,0xC,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0xB,0x23,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x5,0x10,0x80,0x0,0x0,0x0,
0x0,0x0,0x0,0x2,0x88,0x20,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0x38,0x8,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x89,0x42,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x52,0x13,0x0,0x80,0x0,
0x0,0x0,0x0,0x0,0x29,0x36,0x40,0x30,0x0,
0x0,0x0,0x0,0x0,0x10,0xC4,0x70,0x1C,0x0,
0x0,0x0,0x0,0x0,0xE,0x0,0xC0,0x1,0x0,
0x0,0x0,0x0,0x0,0x4,0xFC,0x82,0x0,0x40,
0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x80,0x10,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x40,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x10,0x2,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x4,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x1F,
0xFF,0xFF,0xFF,0x0,0x0,0x8,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x4,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x4,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x4,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x8,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x10,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x60,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x6,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x38,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x60,0x0,0x0,0x0,0x0,0x0,0x10,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x18,
0x0,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0x12,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x9,
0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x83,
0x80,0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x40,
0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x4,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x4,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,
0x0,0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x8,0x0,0x0,0x0,0x0,0x0,
0x20,0x0,0x0,0x4,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x10,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x1,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x1,0xFC,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1F,0xFF,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7F,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7C,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xF8,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xC0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,
};

unsigned char yinghuozhishen[] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x60,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x3,0xE0,0x0,0x0,0x0,0x0,0x0,
0x80,0x0,0x6,0x60,0x0,0x0,0x0,0x6,0x0,
0xC0,0x0,0xC,0x60,0x0,0x0,0x0,0x7,0xF0,
0x40,0x0,0x18,0xE0,0x0,0x0,0x0,0x7,0xF0,
0x60,0x0,0x31,0xE0,0x0,0x0,0x0,0x7,0xF0,
0x3C,0x1,0xE3,0xE0,0x0,0x0,0x0,0x7,0xF0,
0x7,0xFF,0x3,0xE0,0x0,0x0,0x0,0x1E,0x78,
0x0,0x0,0x33,0xE0,0x0,0x0,0x0,0xF,0xFC,
0x0,0x0,0x7F,0xE0,0x0,0x0,0x0,0x1F,0xFC,
0x0,0x1,0xFF,0xF0,0x0,0x0,0x0,0x3,0x90,
0x0,0x3,0xFF,0xF1,0x0,0x0,0x0,0x7,0x0,
0x0,0x7,0xFF,0xF1,0x80,0x0,0x0,0x3,0x80,
0x0,0xF,0xFF,0xF3,0x80,0x0,0x0,0x0,0x0,
0x0,0xF,0xFF,0xF3,0x80,0x0,0x0,0x0,0x0,
0x0,0xDF,0xFF,0x73,0x80,0x0,0x0,0x0,0x0,
0x3,0x29,0xFE,0xFA,0x9C,0x0,0x0,0x0,0x0,
0x7,0x93,0xFF,0x7E,0xBC,0x0,0x0,0x0,0x0,
0xF,0xEF,0xFF,0xDE,0x3C,0x0,0x0,0x0,0x0,
0x1F,0xE7,0xFF,0xF8,0x30,0x0,0x0,0x0,0x0,
0x7F,0xFF,0xFF,0xE8,0x70,0x0,0x0,0x0,0x0,
0xFF,0xFF,0xFF,0xB9,0xBC,0x0,0x0,0x0,0x0,
0xFF,0xFF,0xFF,0x3F,0xFC,0x0,0x0,0x0,0x0,
0x4F,0xFF,0x83,0xCF,0x9E,0x0,0x0,0x0,0x0,
0xF7,0xFF,0x3D,0x9F,0x80,0x0,0x0,0x0,0x0,
0xBF,0xFF,0x6C,0xEF,0x80,0x0,0x0,0x0,0x0,
0x1B,0xFE,0x42,0x9F,0x80,0x0,0x0,0x0,0x0,
0xF,0xFE,0x82,0x75,0x0,0x0,0x0,0x0,0x0,
0xB,0xFE,0x83,0x7C,0x0,0x0,0x0,0x0,0x0,
0xB,0xFE,0x83,0x7C,0x0,0x0,0x0,0x0,0x0,
0xB,0xFE,0x83,0x7C,0x0,0x0,0x0,0x0,0x0,
0xB,0xFE,0x83,0x7C,0x0,0x0,0x0,0x0,0x0,
0xF,0xFE,0x83,0xFC,0x0,0x0,0x0,0x0,0x0,
0xB,0xFE,0x82,0xFC,0x0,0x0,0x0,0x0,0x0,
0x17,0xFE,0xC6,0xFC,0x0,0x0,0x0,0x0,0x1,
0x37,0xFF,0xEE,0xFC,0x0,0x0,0x0,0x0,0x1,
0xF7,0xFF,0x7D,0xFC,0x0,0x0,0x0,0x0,0x1,
0xF,0xFF,0x83,0xFC,0x0,0x0,0x0,0x0,0x0,
0xFF,0xFF,0xFF,0xFC,0x0,0x0,0x0,0x0,0x1F,
0xFF,0xFF,0xFE,0x3C,0x0,0x0,0x0,0x0,0xF,
0xFF,0xFF,0xFF,0xFC,0x3,0xB8,0x0,0x0,0x7,
0xFF,0xFF,0xFE,0x78,0x7,0xFC,0x0,0x0,0x3,
0xFF,0xFF,0xFF,0xF8,0x7,0xFC,0x0,0x0,0x3,
0xFF,0xFF,0xFF,0xF8,0x7,0xFE,0x0,0x0,0x3,
0xFF,0x6F,0xFF,0xF8,0x3,0xDE,0x0,0x0,0x3,
0xFF,0x9F,0xFF,0xF0,0x7,0x7F,0x0,0x0,0x7,
0xFF,0xDF,0xFF,0xF0,0x7,0x3F,0x2C,0x0,0x7,
0xFF,0xDF,0xFF,0xF0,0x7,0xFF,0x38,0x0,0x0,
0xFF,0xDF,0xFF,0xE0,0x7,0xFF,0x7E,0x0,0x0,
0xFF,0xF,0xFF,0xE0,0x33,0xFC,0x7C,0x0,0x0,
0xFE,0xF3,0xFF,0xC0,0x39,0xCE,0x78,0x0,0x0,
0xE5,0xFD,0x5F,0x80,0x3F,0xDC,0x30,0x0,0x0,
0xFF,0xFF,0xFF,0x0,0x1F,0xBE,0x7F,0x80,0x0,
0xFF,0xFF,0xFE,0x0,0xB,0x3F,0xFC,0x0,0x14,
0x7F,0xFF,0xF8,0x0,0xF3,0xFB,0xBE,0x0,0x54,
0xF,0xFF,0xF0,0x1,0xFF,0xFF,0xCC,0x0,0x7C,
0x0,0xFF,0x0,0x1,0xCD,0xFD,0xC4,0x0,0x3D,
0x0,0x0,0x0,0x0,0x1F,0xFF,0x40,0x1,0xFF,
0x0,0x0,0x0,0x0,0x1F,0xCF,0x46,0x1,0xF7,
0x0,0x0,0x0,0x0,0xF,0xE,0xF,0x3,0xFB,
0x0,0x0,0x0,0x0,0xF,0xE,0x1F,0x1,0xFF,
0x0,0x0,0x0,0x0,0x3,0x9E,0x1F,0x1,0xF7,
0x0,0x0,0x5,0x0,0x1,0xFF,0xDF,0x0,0x7F,
0x0,0x0,0x27,0x80,0x0,0xFF,0xEE,0x70,0xFF,
0x0,0x0,0x17,0x80,0x0,0x7,0xFE,0xF8,0x3F,
0x0,0x1,0x9F,0xF0,0x0,0xF,0xFF,0xFC,0x7F,
};

void generateLiu(struct sprite* s) {
//    s->width = 73;
//    s->height = 73;
//    int data_size = s->width * s->height / 8 + 1;
//    s->data = (unsigned char*) malloc(data_size * sizeof(unsigned char));
//    memcpy(s->data, bit_matrix_liu, data_size);

    s->width = 72;
    s->height = 72;
    int data_size = s->width * s->height / 8 + 1;
    s->data = (unsigned char*) malloc(data_size *sizeof(unsigned char));
    memcpy(s->data, yinghuozhishen, data_size);
}
