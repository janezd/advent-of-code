#include "LedControl.h"

char *input = "  R4, R3, R5, L3, L5, R2, L2, R5, L2, R5, R5, R5, R1, R3, L2, L2, L1, R5, L3, R1, L2, R1, L3, L5, L1, R3, L4, R2, R4, L3, L1, R4, L4, R3, L5, L3, R188, R4, L1, R48, L5, R4, R71, R3, L2, R188, L3, R2, L3, R3, L5, L1, R1, L2, L4, L2, R5, L3, R3, R3, R4, L3, L4, R5, L4, L4, R3, R4, L4, R1, L3, L1, L1, R4, R1, L4, R1, L1, L3, R2, L2, R2, L1, R5, R3, R4, L5, R2, R5, L5, R1, R2, L1, L3, R3, R1, R3, L4, R4, L4, L1, R1, L2, L2, L4, R1, L3, R4, L2, R3, L1, L5, R4, R5, R2, R5, R1, R5, R1, R3, L3, L2, L2, L5, R2, L2, R5, R5, L2, R3, L5, R5, L2, R4, R2, L1, R3, L5, R3, R2, R5, L1, R3, L2, R2, R1";
char const *chr = input;
int *end_visit = (int *)input;
int x = 0, y = 0;
int dir = 0;
int steps = 0;
int state = 0;
boolean beep = false;

LedControl lcd(12, 11, 10, 1);

void showNumber(int number, char pos, char width=4) {
    bool negative = number < 0;
    number = abs(number);
    for(int p=pos, w=width; w--; p++) {
        lcd.setChar(0, p, ' ', false);
    }
    for(; width--; pos++) {
        char digit = number % 10;
        number /= 10;
        lcd.setDigit(0, pos, digit, false);
        if (!number) {
            break;
        }
    }
    if (negative) {
        lcd.setChar(0, pos + 1, '-', false);
    }
}

void setup() {
    lcd.shutdown(0, false);
    lcd.setIntensity(0,15);
    lcd.clearDisplay(0);
    pinMode(2, OUTPUT);
    delay(3000);
}

bool already_visited() {
    int cx = 0, cy = 0, nx, ny, minx, miny, maxx, maxy;
    for(int *ptr = (int *)input; ptr != end_visit; ptr += 2) {
        nx = ptr[0];
        ny = ptr[1];
        minx = min(cx, nx);
        maxx = max(cx, nx);
        miny = min(cy, ny);
        maxy = max(cy, ny);
        if ((x >= minx) && (x <= maxx) && (y >= miny) && (y <= miny)) {
            return true;
        }
        cx = nx;
        cy = ny;
    }
    return false;   
}
    

void loop() {
    if (!state) {
        if ((*chr == 'L') || (*chr == 'R')) {
            dir = (4 + dir + (*chr == 'L' ? -1 : 1)) % 4;
            state = 1;
            steps = 0;
        }
    }
    else {
        if ((*chr >= '0') && (*chr <= '9')) {
            steps = 10 * steps + (*chr - '0');
            state++;
        }
        else {
            while(steps--) {
                switch (dir) {
                    case 0: y++; break;
                    case 1: x++; break;
                    case 2: y--; break;
                    case 3: x--; break;
                }
                state = 0;
                showNumber(x, 4);
                showNumber(y, 0);
                digitalWrite(2, HIGH);
                delay(20);
                digitalWrite(2, LOW);
                delay(20);
                if (already_visited()) {
                    chr = NULL;
                    break;
                }
            }
            end_visit[0] = x;
            end_visit[1] = y;
            end_visit += 2;
        }
    }
    if(chr && *chr) {
        chr++;
    }
    else {
        beep = !beep;
        if (beep) {
            showNumber(x, 4);
            showNumber(y, 0);
            tone(2, 430, 300);
        }
        else {
            lcd.clearDisplay(0);
        }
        delay(300);
    }
}
