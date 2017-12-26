#include <stdio.h>
#include <string.h>

#define PROGMEM
extern const char data PROGMEM [];

typedef unsigned char byte;
typedef struct { byte x, y; } coords;

int lengths[8][8];

#define VISIT(x,y) visited[(y - 1) * 22 + ((x - 1) >> 3)] |= (1 << ((x - 1) & 0x7))
#define VISITED(x,y) (visited[(y - 1) * 22 + ((x - 1) >> 3)] & (1 << ((x - 1) & 0x7)))
#define AT_POS(x,y) data[(x) + (178 * (y))]

#define TRY_VISIT(x,y) if ((AT_POS(x,y) != '#') && !VISITED(x,y)) { VISIT(x, y); *innext++ = {(byte)(x), (byte)(y)}; }

void shortest_paths() {
    coords list1[200], list2[200];
    coords *visit, *visit_next, *invisit, *innext;
    byte visited[22 * 43];
    for(char room_no=0; room_no < 7; room_no++) {
        int roompos = strchr(data, room_no + '0') - data;
        byte x = roompos % 178;
        byte y = roompos / 178;
        memset(visited, 0, 22 * 43);
        visit = list1;
        visit_next = list2;
        visit[0] = {x, y};
        VISIT(x, y);
        visit[1].x = 255;
        for(int steps=0; visit->x != 255; steps++) {
            innext = visit_next;
            for(invisit=visit; invisit->x != 255; invisit++) {
                byte x = invisit->x, y = invisit->y;
                char c = AT_POS(x, y);
                if ((c >= '0') && (c <= '9')) {
                    c -= '0';
                    lengths[room_no][c] = lengths[c][room_no] = steps;
                }
                TRY_VISIT(x - 1, y);
                TRY_VISIT(x + 1, y);
                TRY_VISIT(x, y - 1);
                TRY_VISIT(x, y + 1);
            }
            innext->x = 255;
            printf("%li\n", innext - visit_next);
            invisit = visit; visit = visit_next; visit_next = invisit;
        }
    }
}


void salesman() {
    char i;
    int shortest = 10000, shortest_back = 10000;
    char path[8];
    for(i = 0; i < 8; i++)
        path[i] = i;

    for(;;) {
        int path_len = 0;
        for(i = 0; i < 7; i++)
            path_len += lengths[path[i]][path[i + 1]];
        if(path_len < shortest)
            shortest = path_len;
        path_len += lengths[path[7]][0];
        if(path_len < shortest_back)
            shortest_back = path_len;

        for(i=7; i; i--) {
            while((++path[i] <= 7) && memchr(path, path[i], i));
            if (path[i] <= 7)
                break;
            else path[i] = 0;
        }
        if (!i) break;
        while(++i < 8)
            for(; memchr(path, path[i], i); path[i]++);
    }
    printf("Shortest path: %i\n", shortest);
    printf("Shortest path with return: %i\n", shortest_back);
}

int main() {
    shortest_paths();
    salesman();
}


const char data [] PROGMEM = R"x(#################################################################################################################################################################################
#...................#.#.#.........#.........#...............#.....#.....#.........#.............#.............#...#.......#.......#...#...#.......#...#...#.#...#.........#...#.#
#.#.#.#.#.#.#.#.#.#.#.#.#.###.###.#.###.#.#.#.#.#.#.#.#.###.#.#.#.#.#.#.#.#.#######.#####.###.#.###.#.#.#.#.#.#.#.#.###.#.#.#########.#.###.###.#.#.#####.#.#.#####.###.#.#.#.#.#
#...#.....#.#...#...#...#.#...#...#.....#...#.#.....#...#.......#.#.....#...........#.........#.#.....#.#...#.........#.#.....#.........#...#.....#.....#.....#...#.#.....#.....#
#.#.#.###.#.#.#.#.#.#.#.#.#.#.#.###.#####.#.###.###.#.###.###.#.#.#.#####.#####.#.#.#.#.###.#.#.#.#.#.#.#######.#.#.#####.#.#####.###.###.#.#.###.#.#.#.###.###.#.#.#.###.#.#.#.#
#.#.#...#...#...........#.......#...#.#.#.#.....#.#.......#...#...#.#.....#...#...#.#.#...........#.#...#...#...#.....#...........#...#0....#...#.#.#.....#.......#.....#...#...#
#.#.#.#.#.#.#.###########.###.###.###.#.#.#.#.#.#.#########.#####.#.#.###.#.#.#.#.#####.#.#.#.###.#.#.###.###.###.#.#.#.###.#.#.#.#.#######.#.#.#.#.#.###.#######.#######.#####.#
#.....#...#...#.#3........#.......#.#...#.#.#...#.......#.#.......#.#...#...#.#.....#...#.....#...#.#.....#.#.......#.......#...............#...#.......#.......#.#.............#
#.#.#.###.###.#.###.#.###.#.#.#.###.#.###.#.#.#######.#.#.###.#.###.#.#.#.#########.#.#.#####.#.#.#.#.#.#.#.#.#.#####.#####.#.###.###.###.###.#.#.###.#.#.###.###.###.#.###.#.###
#...#.....#.......#.#.#...#.............#...........#...........#.....#.#.......#.....#.......#.......#.#.....#.....#.....#.....#.#...#.......#.......#.#.....#.#...#.....#...#.#
#####.###.###.#.###.###.#.#.#####.#.###.#####.#.#.#.#########.#.#.###.#.#.#.#.#.#.###.###.#.#.###.###.#.#####.#.###.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#####.#.#####.#####.###.#.#.#.#
#.....#.........#.......#.#.......#.#.....#...#...#.............#.....#.......#.#...#...#...#...#.....#...#.....#.....#...#.....#...#.#...#...#...#.....#.....#.......#.#...#...#
#.#.#.#.###.#.#.#.#.#.#.#.#.#####.###.###.#####.#.#.#####.#.###.#.#.#.###.#.#.###.#.###.#.#.#.###.###.#.#.#.#########.###.#.#.#.#.#.#.#.#####.#.###.#.#.#.#.###.#.#.#.#.#.#####.#
#.....#.#.....#.....#.....#.#...............#.#.........#.....#.#.....#.....#...#.....#.#.#.#.#...#...#...............#...#.#...#...#.#.#...#.#.#.....#.....#...#...#.#...#...#.#
#.###.#.#.#.#.#.#.#.#.#####.#.#.###.#.#.###.#.#######.#.#.#.#.#.#.#########.###.#.###.###.#.#.#.#########.#.#.###.#.#.#.###.###.###.###.#.###.#.#.#.#.#.###.#.#.###.#.#.#.#.#.#.#
#.#.#.#.#.#...#...#...#.........#...........#...#...#...#.....#...#.#.#.......#.#.....#...........#.........#.......#...#.#.#...#.........#1#.#...#.#.............#...#.........#
###.#.#.###.#.#.#.#.#.#####.#########.###.#.#.#####.###.###.#.#.#.#.#.#.#.###.#.#.#.#.#.#####.#.#.#####.#######.###.#.#.#.#.#.#.#.###.#.#.#.#.###.#.#.#.#.#.###.#.#####.###.#####
#...#.#.....#.....#.........#...#...#...#...#...#.......#.......#.....#.........#.#...#.....#.#...#.....#...#...#.#.#.......#.....#.....#.#...#.#.............#.#...........#.#.#
#.#.#.#.#.###.###.#.#.###.###.###.#.#.#.#####.#.###.###.#.###.#######.###.#.###.#.#.#.#.#.#.#####.###.#.#.#.#.#.#.###########.#.#.#.#.#.#.#.#.#.#.###.###.#.###.#.#.#.###.#.#.#.#
#.........#...#.....#.#...#...#...............#.....#.......#...#.....#...#.#...#.#...#.#.........#...#.#.#.....#.....#.......#.......#.....#.#...........#.....#.#...........#.#
#####.#.#.#.#.#.###.#.#.#.#.#.#.#####.###.#.#.#.###.#.###.#.#.#.#.#.#.###.#.#.###.#.#.#.#.###.#.#.#.#####.#.#####.###.#.#.#.###.#.#.###.###.###.#####.#.#.#.#.#.#.#.###.#####.#.#
#2..........#...#...#.#...#.#.............#.#.#.......#...#.....#...........#.#...#.#.#.....#.#...#.#.#.........#...#...#.#...#.....#.........#...#...#...#.....#.....#.....#...#
#####.#.#.###.#.#####.###.#.#.#.###.###.###.###.#.###.#.#.#####.#.#.#########.#.###.#.#####.#.#####.#.#.###.#.#.#.#.###.###.#.###.#######.#############.###.###.###.###.###.#.###
#.#.......#...#...#...#.......#...........#...#.#.....#...#.......#.....#...#.....#.#.......#.........#...#.#.....#.#...#.............#.....#.............#.#...#.#...#.......#.#
#.#.#.#####.#.#.###.###.###.#.#.#.#.#.#####.#.#.#.#.###.###.#.#####.#.#####.#.#.###.#.#####.#.###.###.###.#.###.#.#.#.#.#.#########.###.###.#######.###.#.#.#.###.#####.###.#.#.#
#.....#.#...#.#.....#...#.....#...#...#...#.#...#...#.#.......#.#...#.......#.#.#.............#...#...#...#.....#.#.........#...#.#.#...#...#...........#...#.#7#.#.....#.....#.#
###.#.#.#.#.#.#.#.#.#.#.#.###.#.#.###.#.#.#.###.#.#.#.#.#.#####.#.#######.#.###.#.#.#.#.#.#####.###.#.#.#.#.#.#.#.#.#.#.#.###.###.#.#.#.#.###.#.#.###.#.#.#.###.#.###.#.#.###.#.#
#.#...#.....#.#...#.#.......#.#.......#.........#.#.#.#...............#.....#...#.#.........#.......#.#.#.#...#...#.#.#.....#.....#.#.#...#...#...#.#.#.....#...#.....#...#...#.#
#.#####.#######.#.#########.#.#.###.###.#.#####.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.###.#.#####.###.#.#.#.#.#.###.#######.#.#.###.#.#.#.###.###.#.###.###.#.#.###.#.###.#.#.#.#####.#.#
#.#.........#.#.#...#.....#.....#...#.............#...#...#.#.......#...#.#.......#.......#...#.....#...#...#.............#.#.........#...#...#...........#...#.......#.#.....#.#
#.#.#.#######.#.#.#.###.#.#.#.#.###.#.#.#.#.#.#.#.#.#####.#.#.###.#.#.#.#.#.#.#.#.###.###.###.#####.#.#.#####.#.#######.#.#.#.#.###.#.#.#.#.###.#.#.#.#.#.#####.#.#.#.#######.#.#
#...#.#.......#.#...#...........#...#.......#.....#...#.....#.........#.....#...#.........#.#...#...#...#.....#.......#...#.............#.#.........#.....#.....#.....#.#...#.#.#
#.###.#.###.#.###.#.###########.#######.###.#########.#.#.#.#.#.###.###.#.#.#.###.#.###.###.#.#.#.#.#.#.#.###.#.#####.#####.#.###.###.#.#.#.#######.###.#.#.#####.###.#.#.###.#.#
#.#.....#.....#.#.....#4........#...#...#.#.....#...#.#.#...#.#.........#.....#.......#.#.......#.#.....#.....#...............#.....#.#.#.#...#.........#...#...#.........#...#.#
###.#####.#.#.#.#########.#.#.#####.#.#.#.###.###.#.#.#.#.#.###.#.#.###.###.#.###.###.#.###########.###.#.#.#.#.###.#####.#.#.#.#.###.###.#.#.#.#.#.#.#.#.###.###.#.###.#.#.#.#.#
#.........#.#.....#.....#.#.....#.#.#.#...#.....#.......#...#.#...#.....#.......#.....#.........#.......#...#.#.#.......#.......#...#...#...#...#.#.#...#.....#...#...#...#.....#
#.#.###.###.###.###.#.###.#.#.###.###.###.#.#.#.#.#####.###.#.#.#.#.#.###.#.#####.#.###.#.#.#.#.#.#.###.#.###.#.#.#.#.#########.#.#####.#.#.#.#.#####.#.#.#######.#.#.###.###.#.#
#.............#.#...#.#.....#.#...#.........#.....#...#.......#...#.......#.......#...........#...#...#.#...#...#.....#...........#.....#.#...#.....#.....#.#.........#.....#.#.#
#.#.#.###.#.#.#####.###.#.#.#.#.#.#.#.#####.###.#.#.#####.#.#.#.#.#####.#.###.#####.#############.#.#.###.#.#.#.#####.#.#.#.#.#.#.#.###.###.###.#.#.#.###.#.#.#.#.#.#.###.#.###.#
#.#...#.#.#.....#.............#...#.........#...#.#...#...#...#...#...........#.#.#.#.....#...#.....#.#.#...#...#.#.........#.....#.........#...........#.....#...#...#.......#.#
#.#.#.#.#.###.#.#.###.#.#######.#.#.#.#.#.#.#.#.#.###.#.###.###.###.#####.#.###.#.#.###.#.#.#######.#.#.#.###.###.#.###.#####.#.#.#####.#.#.#.#.#####.#.#.#####.#.#####.#########
#.......#.....#...#...#.....#...........#...#.#...#.........#...#.....#...........#.....#.#.....#...#...#.#...#...#...#.....#...........#...#.#...#...#.....#.....#...........#6#
#.#.#.#.#######.###.#.#.###.#.#.###.#####.#.###.#.#######.#.#####.#.#.#.#########.#.###.#.#.#####.#.#.###.#.#########.###.#.#####.###.#.###.#.#.#.###.#.###.#.#.#.#.#.#.#.#####.#
#.....#.............#...#.#...#...#.#5......#...#...#.....#.............#.#.......#.....#.....#...........#.........#...#.#.....#.#.#.#...#...........#.#.#.......#.............#
#################################################################################################################################################################################)x";