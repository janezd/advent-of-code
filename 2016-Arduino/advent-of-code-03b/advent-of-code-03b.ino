#include "LedControl.h"

int nums[9];
int curnum = 0;
int total = 0;

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
    showNumber(0, total);
    pinMode(2, OUTPUT);
    memset(nums, 0, 9 * sizeof(int));
    Serial.begin(9600);
}

void loop() {
    int b;
    if (Serial.available() > 0) {
        b = Serial.read();
        if ((b >= '0') && (b <= '9')) {
            nums[curnum] = 10 * nums[curnum] + b - '0';
        }
        else if (nums[curnum]) {
            showNumber(nums[curnum], 4);
            curnum++;
            if (curnum == 9) {
                for(int i = 3, *nn = nums; i--; nn++) {
                    if ((nn[0] < nn[3] + nn[6]) && (nn[3] < nn[0] + nn[6]) && (nn[6] < nn[0] + nn[3])) {
                        showNumber(++total, 0);
                        digitalWrite(2, HIGH);
                        delay(1);
                        digitalWrite(2, LOW);
                    }
                }
                memset(nums, 0, 9 * sizeof(int));
                curnum = 0;
            }
        }

        if (b == '.') {
            for(;;) {
                lcd.clearDisplay(0);
                showNumber(total, 0);
                tone(2, 430, 300);
                delay(300);
                lcd.setIntensity(0, 2);     
                delay(300);
                lcd.setIntensity(0, 15);     
            }
        }
    }
}
