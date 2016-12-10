#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

short frequencies[8][26];
char i, j;

short argmax(short *f) {
    short *m=f, *t=f;
    for(char i=26; i--; t++) {
        if (*t > *m) {
            m = t;
        }
    }
    return m - f; 
}

short argmin(short *f) {
    short *m=f, *t=f;
    for(char i=26; i--; t++) {
        if (*t < *m) {
            m = t;
        }
    }
    return m - f; 
}

void setup() {
    lcd.begin(16, 2);
    lcd.print("AoC - Day 5");
    lcd.setCursor(0, 1);
    lcd.print("Computing...");
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 26; j++) {
            frequencies[i][j] = 0;
        }
    }
    i = 0;
    Serial.begin(9600);
}

void done() {
    lcd.clear();
    for(i=0; i<8; i++) {
        lcd.setCursor(i, 0);
        lcd.print((char)(97 + argmax(frequencies[i])));
    }
    for(i=0; i<8; i++) {
        lcd.setCursor(i, 1);
        lcd.print((char)(97 + argmin(frequencies[i])));
    }
    for(;;);
}

void loop() {
    if (!Serial.available())
        return;
        
    char b = Serial.read();
    if (b == '.') {
        done();
    }
    else if ((b >= 'a') && (b <= 'z')) {
        frequencies[i][b - 'a']++;
        i++;
    }
    else {
        i = 0;
    }
}
