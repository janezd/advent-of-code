#include <stdio.h>
#include "advent.h"

char a, b, c;
int sum = 0;
char in_brackets;
bool abba[2];
int line = 1;

void reset() {
    in_brackets = 0;
    a = b = c = -1;
    abba[0] = abba[1] = false;
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
    char d = Serial.read();
    if (d == '.') {
        lcd.clearDisplay(0);
        showNumber(sum, 0);
        done();
    }
    if ((d == '[') || (d == ']')) {
        in_brackets = 1 - in_brackets;
        a = b = c = -1;
    }
    else if ((d == '\n') || (d == ' ')) {
        if (abba[0] && !abba[1]) {
            showNumber(++sum, 0);
            digitalWrite(2, HIGH);
            digitalWrite(2, LOW);
        }
        showNumber(++line, 4);
        reset();
    }
    else {
        d -= 'a';
        if ((a == d) && (b == c) && (a != b)) {
            abba[in_brackets] = true;
        }
        a = b;
        b = c;
        c = d;
    }
}
