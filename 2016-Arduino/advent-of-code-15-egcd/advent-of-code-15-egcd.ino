#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

long nums[10][4];
long *numptr = (long *)nums;
bool innum = false;
int discs;
int line = 0;

void egcd(long a, long b, long &sp, long &tp) {
    sp = 1; tp = 0;
    long s = 0, t = 1;
    long k, e;
    while (b) {
        k = a / b;
        e = b; b = a % b; a = e;
        e = s; s = sp - k * s; sp = e;
        e = t; t = tp - k * t; tp = e;
    }
}

long chinese() {
    long long a1 = 0, a2;
    long long n1 = 1, n2;
    long m1, m2, e;
    for(int disc = 0; disc < discs; disc++) {
        if (n1 < n2) {
            e = n1; n2 = n1; n1 = n2;
            e = a1; a2 = a1; a1 = e;
        }
        a2 = nums[disc][0];
        n2 = nums[disc][1];
        egcd(n1, n2, m1, m2);
        a1 = a1 * m2 * n2 + a2 * m1 * n1;
        n1 *= n2;
        a1 %= n1;
        if (a1 < 0) {
            a1 += n1;
        }
        digitalWrite(6, HIGH);
        lcd.setCursor(0, line);
        lcd.print((long)a1);
        delay(100);
        digitalWrite(6, LOW);
        delay(100);
    }
    return a1;
}

void compute() {
    discs = (numptr - (long *)nums) / 4;
    for(int disc = 0; disc < discs; disc++) {
        nums[disc][0] = (2 * nums[disc][1] - (nums[disc][0] + nums[disc][3])) % nums[disc][1];
    }
    line = 0;
    chinese();
    nums[discs][0] = 11 - discs - 1;
    nums[discs][1] = 11;
    discs++;
    line++;
    chinese();
}

void loop() {
    if (!Serial.available()) {
        return;
    }
    
    char c = Serial.read();
    if (c == 'X') {
        compute();
    }
    if ((c >= '0') && (c <= '9')) {
        if(innum) {
            *numptr = *numptr * 10 + c - '0';
        }
        else {
            *numptr = c - '0';
            innum = true;
        }
    }
    else if (innum) {
        numptr++;
        innum = false;
    }
}

void setup() {
    pinMode(6, OUTPUT);
    Serial.begin(9600);
    lcd.begin(16, 2);
}

