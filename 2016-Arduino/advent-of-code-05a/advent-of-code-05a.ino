#include <stdio.h>
#include <string.h>
#include "LedControl.h"
#include "MD5.h"

LedControl lcd(12, 11, 10, 1);

void setup() {
    lcd.shutdown(0, false);
    lcd.setIntensity(0,15);
    lcd.clearDisplay(0);
    pinMode(2, OUTPUT);

    char door_id[] = "ugkcyxxp";
    char mtry[30], *etry = mtry + 30, *ptrtry;
    char ledpos = 8;
    unsigned char md5[16];

    for(long num = 1, cnum;; cnum=++num) {
        ptrtry = etry;
        while(cnum) {
            *--ptrtry = cnum % 10 + '0';
            cnum /= 10;
        }
        ptrtry -= 8;
        memcpy(ptrtry, door_id, 8);
        MD5::make_hash(ptrtry, etry - ptrtry, md5);
        if (!md5[0] && !md5[1] && !(md5[2] & 0xf0)) {
            lcd.setDigit(0, --ledpos, md5[2] & 0xf, false);
            tone(2, 600, 100);
            if (!ledpos) {
                return;
            }
        }
    }
}


void loop() {
    tone(2, 230, 100);
    delay(100);
    lcd.setIntensity(0, 2);     
    delay(100);
    lcd.setIntensity(0, 15);     
}

