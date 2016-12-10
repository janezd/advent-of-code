    #include "LedControl.h"
    
    #include <string.h>
    #include <stdio.h>
    
    LedControl lcd(12, 11, 10, 1);
    
    char counts[26];
    int sector;
    char common[5], *in_commons;
    long total = 0;
    char text[80], *in_text;
    
    void showNumber(long number, char pos, char width=4) {
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
    
    void reset() {
        memset(counts, 0, 26);
        sector = 0;
        in_commons = NULL;
        in_text = text;
    }
    
    void setup() {
        reset();
        lcd.shutdown(0, false);
        lcd.setIntensity(0,15);
        lcd.clearDisplay(0);
        pinMode(2, OUTPUT);
        delay(3000);
        Serial.begin(4800);
    
    }
    
    bool valid_room() {
        int i, j;
        char letters[27];
        for(i = 0; i < 26; i++) {
            for(j = i; (j > 0) && (counts[i] > counts[letters[j - 1]]); j--) {
                letters[j] = letters[j - 1];
            }
            letters[j] = i;
        }
        return !memcmp(common, letters, 5);
    }
    
    void loop() {
        if (!Serial.available())
            return;
            
        char b = Serial.read();
        if (b == '.') {
            done();
        }
        else if ((b >= 'a') && (b <= 'z')) {
            if (!in_commons) {
                counts[b - 'a']++;
                *in_text++ = b;
            }
            else {
                *in_commons++ = b - 'a'; 
            }
        }
        else if (b == '-') {
            *in_text++ = b;
        }
        else if ((b >= '0') && (b <= '9')) {
            sector = sector * 10 + b - '0';
        }
        else if (b == '[') {
            in_commons = common;
        }
        else if (b == ']') {
            if (valid_room()) {
                total += sector;
                showNumber(total, 0, 8);
                digitalWrite(2, HIGH); delay(10); digitalWrite(2, LOW);
            }
            reset();
        }
    }
    
    

