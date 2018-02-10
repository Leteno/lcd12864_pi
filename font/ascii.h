#ifndef ASCII_H
#define ASCII_H

struct word {
    int row;
    int width;
    unsigned char* data;
};

struct word getAsciiWord(unsigned char ascii);
void freeWord(struct word w);

#endif
