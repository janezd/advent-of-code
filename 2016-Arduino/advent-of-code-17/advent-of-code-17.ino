#include <stdio.h>
#include <string.h>
#include <LiquidCrystal.h>
#include "MD5.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char path[600];
char salt[] = "pslxynzg";
char *lastsalt = path + 7;
char *end = path + 8;
char *cnt;
int longest = 0;
int shortest = 600;

unsigned char md5[16];

void setup() {
    lcd.begin(16, 2);

    strcpy(path, salt);
    for(;;) {
        for(; *end == 'R'; end--);
        if (end == lastsalt)
            break;
        end[1] = 0;
        MD5::make_hash(path, end - path, md5);
        char allowed;
        switch (*end) {
            case 0: *end = 'U'; allowed = md5[0] >> 4; break;
            case 'U': *end = 'D'; allowed = md5[0] & 0xf; break;
            case 'D': *end = 'L'; allowed = md5[1] >> 4; break;
            case 'L': *end = 'R'; allowed = md5[1] & 0xf; break;
        }
        if (allowed > 0xa) {
            int x = 0, y = 0;
            for(cnt = lastsalt; cnt != end; ) {
                char c = *(++cnt);
                switch (c) {
                    case 'U': y -= 1; break;
                    case 'D': y += 1; break;
                    case 'L': x -= 1; break;
                    case 'R': x += 1; break;
                }
            }
            if ((x >= 0) && (x <= 3) && (y >= 0) && (y <= 3)) {
                if ((x == 3) && (y == 3)) {
                    int length = end - lastsalt;
                    if (length > longest) {
                        longest = length;
                    }
                    if (length < shortest) {
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print(lastsalt + 1);
                        shortest = length;
                    }
                }
                else {
                    *++end = 0;
                    end[1] = 0;
                }
            }
        }
    }
    lcd.setCursor(0, 1);
    lcd.print("Longest:");
    lcd.print(longest);
}

void loop() {}
