#include <wiringPi.h>
#include <stdio.h>

#include "switch_util.h"

#define PIN_A 8
#define PIN_B 9

#define PIN_LED 7

void switch_util_setup() {
    wiringPiSetup(); // TODO lcd12864_util.c
    pinMode(PIN_A, INPUT);
}

unsigned int getButton() {
    int result = 0;
    if (LOW == digitalRead(PIN_A)) {
	result |= BTN_A;
    }
    if (LOW == digitalRead(PIN_B)) {
	result |= BTN_B;
    }
    return result;
}

void switch_util_test() {
    switch_util_setup();
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);

    int btn;
    for(;;) {
	btn = getButton();
	if (BTN_A & btn) {
	    digitalWrite(PIN_LED, HIGH);
	}
	if (BTN_B & btn) {
	    digitalWrite(PIN_LED, LOW);
	}
    }
}
