#include <stdio.h>
#include "advent.h"

enum {Normal, Read_NChars, Read_Times};
char state = Normal;
long nchars, times;
long long length = 0;
long skip_chars = 0;

void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(38400);
}

void loop() {
    if (!Serial.available())
        return;
        
    char c = Serial.read();
    if(skip_chars) {
        skip_chars--;
        return;
    }
    if (c <= 32) {
        Serial.print((long)length);
        done();
    }
    switch(state) {
        case Normal:
            if (c == '(') {
                state = Read_NChars;
                nchars = 0;
            }
            else {
                length++;
            }
            break;
        case Read_NChars:
            if (c == 'x') {
                state = Read_Times;
                times = 0;
            }
            else {
                nchars = nchars * 10 + c - '0';
            }
            break;
        case Read_Times:
            if (c == ')') {
                state = Normal;
                length += times * nchars;
                digitalWrite(2, HIGH);
                showNumber(length, 0, 8);
                skip_chars = nchars;
                digitalWrite(2, LOW);
            }
            else {
                times = times * 10 + c - '0';
            }
            break;
    }
}

