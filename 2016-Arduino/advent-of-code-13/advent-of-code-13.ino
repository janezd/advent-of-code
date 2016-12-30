#include "advent.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, 6, 7);

#define N 1364

unsigned char maze[48][12];
uint8_t bitmap[48][6];
int visited = 1;

inline char get(char x, char y) { return (maze[y][x >> 2] >> ((x & 3) << 1)) & 3; }
inline void set(char x, char y, unsigned char v) {
    unsigned char &c = maze[y][x >> 2], shift = (x & 3) << 1;
    c = (c & (0xff ^ (3 << shift))) | (v << shift);
    }

void compute_map() {
    for(int y = 0; y < 48; y++) {
        for(int x = 0; x < 48; x++) {
            long n = x * (x + 3 + 2 * y) + y * (1 + y) + N;
            char odd = 1;
            while(n) {
                odd ^= (n & 1);
                n >>= 1;
            }
            set(x, y, odd ? 0 : 3);
        }
    }
}

void print_map() {
    memset(bitmap, 48 * 6, 0);
    for(int y = 0; y < 48; y++) {
        for(int x = 0; x < 48; x++) {
            if (get(x, y)) {
                bitmap[y][x >> 3] |= 1 << (x & 7);
            }
        }
    }
    u8g2.firstPage();
    do {
        u8g2.drawBitmap(0, 16, 6, 48, (uint8_t *)bitmap);
    } while (u8g2.nextPage());
}

#define INC(x, y) { if (!get(x, y)) set(x, y, 3 - exp_now); }

bool expand(char exp_now) {
    for(int x = 0; x < 48; x++) {
        for(int y = 0; y < 48; y++) {
            if (get(x, y) == exp_now) {
                visited++;
                if ((x == 31) && (y == 39)) return true;
                if (x) INC(x - 1, y);
                if (x < 35) INC(x + 1, y);
                if (y) INC(x, y - 1);
                if (y < 40) INC(x, y + 1);
                set(x, y, 3);
            }
        }
    }
    return false;
}

void setup() {
    compute_map();
    u8g2.begin();
    u8g2.setPowerSave(0);
    set(1, 1, 1);
    pinMode(2, OUTPUT);
}

int steps = 0;
char exp_now = 1;
void loop() {
    digitalWrite(2, HIGH);
    //print_map();
    digitalWrite(2, LOW);
    showNumber(steps, 0);
    if (steps <= 50) {
        showNumber(visited, 4);
    }
    if (expand(exp_now)) {
        done();
    }
    steps++;
    exp_now = 3 - exp_now;
}

/*
void loop() {
  // put your main code here, to run repeatedly:
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0,60,"Hello World!");
  } while ( u8g2.nextPage() );
  delay(1000);
}*/
