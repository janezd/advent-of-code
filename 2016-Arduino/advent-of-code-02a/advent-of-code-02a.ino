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



void loop() {
    if (Serial.available() > 0) {
        switch(Serial.read()) {
            case 'R': if (pos % 3) pos++; break;
            case 'L': if (pos % 3 != 1) pos--; break;
            case 'U': if (pos >= 4) pos -= 3; break;
            case 'D': if (pos <= 6) pos += 3; break;
            default: lcd.setDigit(0, digit, pos, false); tone(2, 430, 30); delay(30); digit--;
        }
        lcd.setDigit(0, digit, pos, false);
        digitalWrite(2, HIGH);
        delay(1);
        digitalWrite(2, LOW);
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
