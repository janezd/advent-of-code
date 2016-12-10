#include "advent.h"

void showNumber(long long number, char pos, char width) {
    if (!lcd_initialized) {
        lcd.shutdown(0, false);
        lcd.setIntensity(0,15);
        lcd.clearDisplay(0);
        lcd_initialized = true;
    }
    for(int p=pos, w=width; w--; p++) {
        lcd.setChar(0, p, ' ', false);
    }
    for(; width--; pos++) {
        char digit = number % 10L;
        number /= 10L;
        lcd.setDigit(0, pos, digit, false);
        if (!number) {
            break;
        }
    }
}

void done() {
    for(;;) {
        tone(2, 230, 100);
        delay(100);
        lcd.setIntensity(0, 2);     
        delay(100);
        lcd.setIntensity(0, 15);     
    }
}

void tick(int d) {
    digitalWrite(2, HIGH);
    delay(d);
    digitalWrite(2, LOW);
    delay(d);    
}
