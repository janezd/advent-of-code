#include "advent.h"

#define N 100
char row1[N + 1] = "^^.^..^.....^..^..^^...^^.^....^^^.^.^^....^.^^^...^^^^.^^^^.^..^^^^.^^.^.^.^.^.^^...^^..^^^..^.^^^^";
char row2[N + 1];
char *ths = row1, *nxt = row2, *t;
long safe = 0, safe40;

void setup() {
    pinMode(2, OUTPUT);
    for(long i = 0; i < 400000; i++) {
        if (i == 40)
            safe40 = safe;
        if (i % 1000 == 0) {
            digitalWrite(2, HIGH);
            showNumber(i, 0, 8);
            digitalWrite(2, LOW);
        }
        for(int j = 0; j < N; j++) {
            if (ths[j] == '.') {
                safe++;
            }
            const char l = j ? ths[j - 1] : '.';
            const char r = j + 1 < N ? ths[j + 1] : '.';
            nxt[j] = l == r ? '.' : '^';
        }
        t = ths;
        ths = nxt;
        nxt = t;
    }
}

void loop() {
    showNumber(safe40, 0, 8);
    tone(2, 200, 50);
    delay(1000);
    showNumber(safe, 0, 8);
    tone(2, 220, 50);
    delay(1000);
}

