
#include <wiringPi.h>
#include "lcd12864_util.h"

void write_on_data_bus(unsigned char data) {
    int t[8];
    int f=0,i=0,d=data;

    //进制转换
    for(i=0;i<8;i++){
	t[i]= data % 2; // TODO   use & >> instead
	data= data / 2;
    }

    //输出
    digitalWrite(D1,t[0]);
    digitalWrite(D2,t[1]);
    digitalWrite(D3,t[2]);
    digitalWrite(D4,t[3]);
    digitalWrite(D5,t[4]);
    digitalWrite(D6,t[5]);
    digitalWrite(D7,t[6]);
    digitalWrite(D8,t[7]);
}

void init_env() {
    wiringPiSetup();
    pinMode(D1, OUTPUT);	//设置GPIO
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);

    pinMode(LCD_RS, OUTPUT);
    pinMode(LCD_RW, OUTPUT);
    pinMode(LCD_EN, OUTPUT);

    clear_screen();
    set_echo_state(1, 0, 0);
}

void busy_check() {
    digitalWrite(LCD_RS,0);
    digitalWrite(LCD_RW,1);
    digitalWrite(LCD_EN,1);
    write_on_data_bus(0xff);
    pinMode(D8, INPUT);
    while(digitalRead(D8));
    pinMode(D8, OUTPUT);
    digitalWrite(LCD_EN,0);
}

void write_cmd_LCD12864(unsigned char cmdcode) {
    busy_check();
    digitalWrite(LCD_RS,0);
    digitalWrite(LCD_RW,0);
    digitalWrite(LCD_EN,1);
    //delay(1);
    write_on_data_bus(cmdcode);
    digitalWrite(LCD_EN,0);
    //delay(1);
}

void write_on_ram(unsigned char data) {
    busy_check();
    digitalWrite(LCD_RS, 1);
    digitalWrite(LCD_RW, 0);
    digitalWrite(LCD_EN, 1);
    //delay(1);
    write_on_data_bus(data);
    digitalWrite(LCD_EN, 0);
    //delay(1);
}

void clear_screen() { // this will reset ddram to 00H
    write_cmd_LCD12864(0x1);
}

void set_echo_state(int wholeEcho, int cursorOn, int cursorPositionOn) {
    int cmd = 0x8;
    if (wholeEcho > 0) cmd |= 0x4;
    if (cursorOn > 0) cmd |= 0x2;
    if (cursorPositionOn > 0) cmd |= 0x1;
    write_cmd_LCD12864(cmd);
}

void set_graphic_on(int on) {
    unsigned char cmd = on > 0 ? 0x36 : 0x34;
    write_cmd_LCD12864(cmd);
}

void set_gdram_address(unsigned char x, unsigned char y) {
    x = x | 0x80;
    y = y | 0x80;
    write_cmd_LCD12864(x);
    write_cmd_LCD12864(y);
}

void clear_graphic_mem() {
    unsigned char col=0, row=0;
    for (row = 0; row < 32; row++) {
	set_graphic_on(0);
	set_gdram_address(row, 0x0);
	for (col = 0; col < 16; col++) {
	    write_on_ram(0x0);
	    write_on_ram(0x0);
	}
	set_graphic_on(1);
    }
}
