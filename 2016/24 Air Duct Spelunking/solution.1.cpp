#include <stdio.h>

typedef unsigned char byte;
typedef struct {byte x, y} coords;

byte maze[23 * 45];
byte x = 0, y = 0;
coords rooms[8];

#define BLOCK(x,y) maze[(y) * 23 + ((x) >> 3)] |= (1 << ((x) & 0x7))
#define BLOCKED(x,y) (maze[(y) * 23 + ((x) >> 3)] & (1 << ((x) & 0x7)))

void done() {
    for(y = 0; y < 45; y++) {
        for(x = 0; x < 177; x++)
            printf("%c", BLOCKED(x, y) ? '#' : ' ');
        printf("\n");
    }
}

void setup() {
    x = y = 0;
}

void loop() {
/*    if (!Serial.available()) return;
    char c = Serial.read(); */
    char c = getchar();
    if (c == '\n')
        if (++y == 45) done();
        else { x = 0; return; }
    else if (c == '#')
        BLOCK(x, y);
    else if ((c >= '0') && (c <= '7')) {
        rooms[c - '0'].x = x;
        rooms[c - '0'].y = y;
    };
    x++;
}

int main() {
    setup();
    for(;;) loop();
}