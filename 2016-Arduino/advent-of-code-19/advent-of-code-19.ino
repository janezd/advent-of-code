#include "advent.h"

#define N 3014387


long m, n;

void setup() {
    for(m = 1; m < N; m *= 2);
    m = (N ^ (m >> 1)) << 1;

    for(n = 1; n < N; n *= 3);
    n /= 3;
    if (N <= 2 * n)
        n = N - n;
    else
        n = 2 * N - 3 * n;
}

void loop() {
    pinMode(2, OUTPUT);
    showNumber(m, 0, 8);
    tone(2, 200, 50);
    delay(1000);
    showNumber(n, 0, 8);
    tone(2, 220, 50);
    delay(1000);
}
