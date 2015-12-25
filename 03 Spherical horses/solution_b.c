#include <stdio.h>
#include <stdlib.h>

/* Solultion for arbitrary number of Santas */

#define N_SANTAS 1

int main(int argc, char *argv[]) {
    typedef struct { int x, y; } COORDS;
    long size = 1000;
    COORDS *coords = calloc(size, sizeof(COORDS)), *scoords, *ecoords = coords + 1;
    int *x = calloc(N_SANTAS, sizeof(int)), *y = calloc(N_SANTAS, sizeof(int));
    int santa = 0;
    char c;
    while((c=getchar()) != EOF) {
        switch (c) {
            case '^': y[santa]--; break;
            case 'v': y[santa]++; break;
            case '<': x[santa]--; break;
            case '>': x[santa]++; break;
        }
        for(scoords = coords; (scoords != ecoords) && ((x[santa] != scoords->x) || (y[santa] != scoords->y)); scoords++);
        /* New house got a gift */
        if (scoords == ecoords) {
            /* C is mostly about memory management !@%!#$& */
            if (ecoords == coords + size) {
                size += 1000;
                coords = realloc(coords, size * sizeof(COORDS));
                ecoords = coords + size - 1000;
            }
            ecoords->x = x[santa];
            ecoords->y = y[santa];
            ecoords++;
        }
        santa = (santa + 1) % N_SANTAS;
    }
    printf("Visited houses: %ld\n", ecoords - coords);
    free(coords); free(x); free(y); /* Not that anybody cares about it here. */
}
