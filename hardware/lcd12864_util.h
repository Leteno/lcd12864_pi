#ifndef LCD12864_UTIL_H
#define LCD12864_UTIL_H

#define LCD_RS 4 //显示屏控制线
#define LCD_RW 5
#define LCD_EN 1

#define D1 30 //显示屏数据线
#define D2 21
#define D3 22
#define D4 23
#define D5 24
#define D6 25
#define D7 26
#define D8 27

void init_env();

void busy_check();

void write_cmd_LCD12864(unsigned char cmd);

void write_on_ram(unsigned char data);

void clear_screen();

void set_echo_state(int wholeEcho, int cursorOn, int cursorPositionOn);

void set_graphic_on(int on);

void set_gdram_address(unsigned char x, unsigned char y);

void clear_graphic_mem();

#endif
