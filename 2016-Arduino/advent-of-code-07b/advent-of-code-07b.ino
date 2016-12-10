#include <stdio.h>
#include "advent.h"

#define N2 (26 * 26)
char a, b;
int sum = 0;
bool in_brackets;
char pairs[N2];
int line = 1;

void reset() {
    in_brackets = false;
    a = b = -1;
    for(int i = 0; i < N2; i++) {
        pairs[i] = 0;
    }
}

void setup() {
    showNumber(0, 0);
    showNumber(line, 4);
    pinMode(2, OUTPUT);
    reset();
    Serial.begin(57600);
}

void loop() {
    if (!Serial.available()) {
        return;
    }
    char c = Serial.read();
    if (c == '.') {
        lcd.clearDisplay(0);
        showNumber(sum, 0);
        done();
    }
    else if ((c == '[') or (c == ']')) {
        in_brackets = !in_brackets;
        a = b = -1;
    }
    else if ((c == '\n') || (c == ' ')) {
        if (memchr(pairs, 3, N2)) {
            showNumber(++sum, 0);
            digitalWrite(2, HIGH);
            digitalWrite(2, LOW);
        }
        showNumber(++line, 4);
        reset();
    }
    else {
        c -= 'a';
        if ((a == c) && (a != b)) {
            if (in_brackets) {
                pairs[a * 26 + b] |= 2;
            }
            else {
                pairs[a + b * 26] |= 1;
            }
        }
        a = b;
        b = c;
    }
}

