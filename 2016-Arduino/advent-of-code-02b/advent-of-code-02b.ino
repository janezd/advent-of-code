#include "LedControl.h"

int pos = 5;
int digit = 4;

LedControl lcd(12, 11, 10, 1);

void setup() {
    lcd.shutdown(0, false);
    lcd.setIntensity(0,15);
    lcd.clearDisplay(0);
    pinMode(2, OUTPUT);
    delay(3000);
    Serial.begin(1200);
}


//          1  2  3  4  5   6   7   8  9  A   B  C  D
int d[] = {0, 3, 6, 7, 8, 0, 10, 11, 12, 0, 0, 13, 0, 0};
int u[] = {0, 0, 0, 1, 0, 0, 2,   3,  4, 0, 6,  7, 8, 11};
int l[] = {0, 0, 0, 2, 3, 0, 5,   6,  7, 8, 0, 10, 11, 0};
int r[] = {0, 0, 3, 4, 0, 6, 7,   8,  9, 0, 11, 12, 0, 0};

void loop() {
    int next;
    if (Serial.available() > 0) {
        switch(Serial.read()) {
            case 'D': next = d[pos]; break;
            case 'U': next = u[pos]; break;
            case 'L': next = l[pos]; break;
            case 'R': next = r[pos]; break;
            default: next = 0; tone(2, 430, 30); delay(30); digit--; 
        }
        if (next) {
            pos = next;
            lcd.setDigit(0, digit, pos, false);
            digitalWrite(2, HIGH);
            delay(5);
            digitalWrite(2, LOW);
            delay(5);
        }
        if (digit == -1) {
             for(;;) {
                  tone(2, 430, 300);
                  delay(300);
                  lcd.setIntensity(0, 2);     
                  delay(300);
                  lcd.setIntensity(0, 15);     
             }
        }
    }
}
