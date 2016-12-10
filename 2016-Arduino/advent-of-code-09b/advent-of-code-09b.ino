#include <stdio.h>
#include "advent.h"

long long compute_length(int n) {
    enum {Normal, Read_NChars, Read_Times};
    long long length = 0;
    char state = Normal;
    int nchars, times;

    while(n) {
        if (!Serial.available())
            continue;
            
        char c = Serial.read();
        if (c <= 32) {
            return length;
        }
        n--;
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
                    length += times * compute_length(nchars);
                    n -= nchars;
                    digitalWrite(2, HIGH);
                    showNumber(nchars, 4);
                    showNumber(times, 0);
                    digitalWrite(2, LOW);
                }
                else {
                    times = times * 10 + c - '0';
                }
                break;
        }
    }
    return length;
}

long long tot_length;

void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(9600);
    tot_length = compute_length(100000);
}

void loop() {
    for(int pos = -11; pos < 8; pos++) {
        lcd.clearDisplay(0);
        showNumber(tot_length, pos, 12);
        tone(2, 30, 290);
        delay(300);
    }
}

