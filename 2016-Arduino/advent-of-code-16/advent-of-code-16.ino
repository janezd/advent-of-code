#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char seed[] = "11101000110010100";
char seedlen = 17;

char dragon(long i) {
    long rep = i / (seedlen + 1);
    char inre = i % (seedlen + 1);
    if (inre == seedlen) {
        rep++;
        return (((rep & -rep) << 1) & rep) != 0;
    }
    else if (rep & 1)
        return '1' - seed[seedlen - inre - 1];
    else
        return seed[inre] - '0';
}

void compute(long long n, char *res) {
    char stack[32], *ptr;
    long chunk_size = n & -n;
    long counter = 0;
    for(unsigned char chunks = n / chunk_size; chunks--;) {
        ptr = stack;
        for(long i = 1; i <= chunk_size; i++) {
            *ptr++ = dragon(counter++);
            if (counter % 100000 == 0) { Serial.println((long)counter); }
            for(long j = i; !(j & 1); j >>= 1) {
                char p1 = *--ptr;
                char p2 = *--ptr;
                *ptr++ = (p1 == p2);
            }
        }
        *res++ = '0' + *stack;
    }
    *res = 0;
}

char res1[32], res2[32];

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("AoC - Day 16");
    
    lcd.setCursor(0, 1);
    lcd.print("Computing part 1");
    compute(272, res1);
    lcd.setCursor(0, 0);
    lcd.print(res1);
    
    lcd.setCursor(0, 1);
    lcd.print("Computing part 2");
    compute(35651584, res2);
}

void loop() {
    for(char i = 0; i < 2; i++) {
        lcd.setCursor(0, 0);
        lcd.print(res1 + i);
        lcd.setCursor(0, 1);
        lcd.print(res2 + i);
        delay(1000);
    }
}

