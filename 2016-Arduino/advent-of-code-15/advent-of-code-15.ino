#include <advent.h>
#include "advent.h"

long nums[10][4];
long *numptr = (long *)nums;
bool innum = false;
int discs;
long i = 0;

long findrot() {
    for(;; i++) {
        if (i % 100 == 0)
            showNumber(i, 0, 8);
        int disc;
        for(disc = 0; (disc < discs) && !((nums[disc][3] + i) % nums[disc][1]); disc++);
        if (disc == discs) {
            Serial.println(i);
            return i;
        }
    }
}

void compute() {
    discs = (numptr - (long *)nums) / 4;
    for(int j = 0; j < discs; j++) {
        nums[j][3] += j + 1;
    }
    long num1 = findrot();
    showNumber(num1, 0, 8);

    nums[discs][3] = discs + 1;
    nums[discs][1] = 11;
    discs++;
    long num2 = findrot();

    for(;;) {
        showNumber(num1, 0, 8);
        tone(2, 200, 100);
        delay(1000);
        showNumber(num2, 0, 8);
        tone(2, 220, 100);
        delay(1000);
    }
}

void loop() {
    if (!Serial.available()) {
        return;
    }
    
    char c = Serial.read();
    if (c == 'X') {
        showNumber(0, 0);
        compute();
    }
    if ((c >= '0') && (c <= '9')) {
        if(innum) {
            *numptr = *numptr * 10 + c - '0';
        }
        else {
            *numptr = c - '0';
            innum = true;
        }
    }
    else if (innum) {
        numptr++;
        innum = false;
    }
}

void setup() {
    pinMode(2, OUTPUT);
    Serial.begin(9600);
}

