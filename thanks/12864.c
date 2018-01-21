/*
	运行：sudo ./12864 [字符]
	编译：gcc 12864.c -o 12864 -L lib -l wiringPi (需已安装wiringPi)
	by：WuSiYu
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <iconv.h>
 
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
 
char u2g_out[255]; 
 
/*===================================================================
功能：编码转换
输入：UTF8
输出：GB2312
====================================================================*/
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen){
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;
 
	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;
	memset(outbuf,0,outlen);
	if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
	iconv_close(cd);
	return 0;
}
 
int u2g(char *inbuf,int inlen,char *outbuf,int outlen){ 
	return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen); 
} 
 
/*===================================================================
功能：总线写入
输入：十六进制数据
输出：无
====================================================================*/
void bus_write(unsigned char data){
	int t[10];
	int f=0,i=0,d=data;
 
	//进制转换
	for(i=0;i<8;i++){
		t[i]=data%2;
		data=data/2;
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
/*===================================================================
功能：检查LCD忙状态                                                    
输入：无
输出：lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      
====================================================================*/
void chk_busy(){//检查忙位
	digitalWrite(LCD_RS,0);
	digitalWrite(LCD_RW,1);
	digitalWrite(LCD_EN,1);
	bus_write(0xff);
	pinMode(D8, INPUT);
	while(digitalRead(D8));
	pinMode(D8, OUTPUT);
	digitalWrite(LCD_EN,0);
}
/*====================================================================
功能：写命令
输入：8位数据
输出：无
=====================================================================*/
void WriteCmd_LCD12864(unsigned char cmdcode){
	chk_busy();
	digitalWrite(LCD_RS,0);
	digitalWrite(LCD_RW,0);
	digitalWrite(LCD_EN,1);
	delay(5);
	bus_write(cmdcode);
	digitalWrite(LCD_EN,0);
	delay(5);
}
/*====================================================================
功能：写数据
输入：8位数据
输出：无
=====================================================================*/
void WriteData_LCD12864(unsigned char Dispdata){
	chk_busy();
	digitalWrite(LCD_RS,1);
	digitalWrite(LCD_RW,0);
	digitalWrite(LCD_EN,1);
	delay(5);
	bus_write(Dispdata);
	digitalWrite(LCD_EN,0);
	delay(5);
}
/*==========================================================================
功能：发送字符串
输入：地址，字符串
输出：无
===========================================================================*/
void WriteWord_LCD12864(unsigned char a,unsigned char *d){//向LCD指定位置发送一个字符串,长度64字符之内。
	unsigned char *s;
	u2g(d,strlen(d),u2g_out,255);
	s=u2g_out;
	WriteCmd_LCD12864(a);
	while(*s>0){
		WriteData_LCD12864(*s); 
		s++;
	}
}
/*==========================================================================
功能：发送字符串2
输入：字符串
输出：无
===========================================================================*/
void WriteWord_LCD12864_2(unsigned char *d){//向LCD发送一屏字符串,长度64字符之内。
	int i=0;
	unsigned char *s;
	u2g(d,strlen(d),u2g_out,255);
	s=u2g_out;
	WriteCmd_LCD12864(0x80);
	while(*s>0){
		WriteData_LCD12864(*s); 
		s++;
		i++;
		if(i==16){
			WriteCmd_LCD12864(0x90);
		}
		if(i==32){
			WriteCmd_LCD12864(0x88);
		}
		if(i==48){
			WriteCmd_LCD12864(0x98);
		}
	}
}
/*==========================================================================
功能：初始化LCD
输入：无
输出：无
===========================================================================*/
void Init_LCD12864(void){			//初始化LCD屏
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
 
	WriteCmd_LCD12864(0x38);       //选择8bit数据流
	delay(20);
	WriteCmd_LCD12864(0x01);       //清除显示，并且设定地址指针为00H
	delay(20);
	WriteCmd_LCD12864(0x0c);       //开显示(无游标、不反白)
	delay(20);
}
 
int main (int args, char *argv[]){
	wiringPiSetup();
	Init_LCD12864();
 
	WriteCmd_LCD12864(0x01);
	WriteWord_LCD12864(0x80,"Hello LCD12864");
	if(argv[1]){
		WriteCmd_LCD12864(0x01);
		WriteCmd_LCD12864(0x80);
		WriteWord_LCD12864_2(argv[1]);
	}
}
