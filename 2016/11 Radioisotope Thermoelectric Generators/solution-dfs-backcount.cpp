#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define N 7

// No local variables, so recursion takes as little space as possible
unsigned char max_steps;
unsigned char stack[70 * 4], *sp = stack, *tsp;
unsigned char curr_floor, floors[8], next_floors[8], next_floor;
unsigned char try_next[10 * 5], *try_end;
unsigned char el1, el2, t;
char ise1, ise2;
unsigned char encoded[4], minmo, move_number;
unsigned char *tptr;
char direction;

unsigned char initial[] = {1 + 2 + 32 + 64, 1 + 2 + 32 + 64,
                                    8 + 16,     4 +  8 + 16,
                                         4,               0,
                                         0,               0};

#define INVALID(state) ((state)[1] && (*(state) & ~(state)[1]))

// Heuristics that computes the lower bound for the number of moves
unsigned char min_moves(char floor, unsigned char floors[8]) {
    unsigned char mfloors[4], x, i, moves;

    // count items to move
    for(i = 0; i < 4; i++) {
        x = floors[2 * i];
        mfloors[i] = 0;
        for(; x; x >>= 1)
            mfloors[i] += x & 1;
        x = floors[2 * i + 1];
        for(; x; x >>= 1)
            mfloors[i] += x & 1;
    }

    // move the elevator (and one item) to the lowest floor
    for(i = 0; (i < 3) && !floors[2 * i] && !floors[2 * i + 1]; i++);
    mfloors[i] += 1; mfloors[floor] -= 1;
    moves = floor - i;

    // bring everything from the lowest floor
    for(i = 0; i < 3; i++) {
        if (mfloors[i] > 2)
            moves += 2 * (mfloors[i] - 2); // bring one thing up, move down again
        if (mfloors[i])
            moves++; // bring the last two (or one)
        mfloors[i + 1] += mfloors[i]; // everything is now one floor higher
    }
    return moves;
}


void print_state() {
    unsigned char fle, flg, fl;
    for(t = (sp - stack) / 4; t--; ) printf(" ");
    printf("%li ", (sp - stack) / 4);
    printf("[[%i]]: ", curr_floor);    
    for(unsigned char bit = 0; bit < N; bit++) {
        flg = fle = 4;
        for(fl = 0; fl < 4; fl++) {
            if (floors[2 * fl] & (1 << bit)) flg = fl;
            if (floors[2 * fl + 1] & (1 << bit)) fle = fl;
        }
        if (fle != 4)
            printf("[%i %i] ", flg, fle);
    }
    printf(" (%i to finish)\n", min_moves(curr_floor, floors));
}

// Uniquely (w.r.t. symmetries) encode the position in 4 bytes
void encode(unsigned char floors[8], unsigned char floor, unsigned char encoded[4]) {
    unsigned char transient[8];
    unsigned char fle, flg, fl;
    for(unsigned char bit = 0; bit < N; bit++) {
        for(fl = 0; fl < 4; fl++) {
            if (floors[2 * fl] & (1 << bit)) flg = fl;
            if (floors[2 * fl + 1] & (1 << bit)) fle = fl;
        }
        fle = flg << 2 | fle; 
        for(flg = bit; flg && (transient[flg - 1] > fle); flg--) {
            transient[flg] = transient[flg - 1];
        }
        transient[flg] = fle;
    }
    transient[7] = floor;
    for(fl = 0; fl < 4; fl++) {
        encoded[fl] = transient[2 * fl] + (transient[2 * fl + 1] << 4);
    }
}


// Decode the position; decoding is exact up to the symmetry
void decode(unsigned char encoded[4], unsigned char floors[8], unsigned char &floor)
{
    unsigned char bit = 1;
    memset(floors, 0, 8);
    for(unsigned char e = 0; e < 4; e++) {
        unsigned char te = encoded[e];
        floors[2 * ((te >> 2) & 3)] |= bit;
        floors[1 + 2 * (te & 3)] |= bit;        
        bit <<= 1;
        if (e < 3) {
            floors[2 * (te >> 6)] |= bit;
            floors[1 + 2 * ((te >> 4) & 3)] |= bit;
            bit <<= 1;
        }
        else {
            floor = te >> 4;
        }
    }
}

bool valid() {
    next_floor = curr_floor + direction;
    if (next_floor > 3)
        return false;

//    printf("%i %i %i %i %i\n", direction, el1, ise1, el2, ise2);
    if ((el1 > 127) || (ise2 < 0) || (ise1 > 1) || (direction > 1) ||
        (!ise2 && !el2) || // try empty just once
        (!(floors[2 * curr_floor + ise1] & el1)) || // no el1
        (el2 && !(floors[2 * curr_floor + ise2] & el2))) // no el2
            return false;

    if (direction == -1) {
        for(t = 0; (t < 2 * curr_floor) && !floors[t]; t++);
        if (t == 2 * curr_floor)
            return false;  // no reason to move down - nothing there
    }

    memcpy(next_floors, floors, 8);
    next_floors[2 * curr_floor + ise1] ^= el1;
    next_floors[2 * curr_floor + ise2] ^= el2;
    if (INVALID(next_floors + 2 * curr_floor))
        return false;
    next_floors[2 * next_floor + ise1] |= el1;
    next_floors[2 * next_floor + ise2] |= el2;
    if (INVALID(next_floors + 2 * next_floor))
        return false;
    
    move_number++;
    return true;
}

bool next() {
    do {
        do {
            do {
                do {
                    do {
                        if (el2 > 0) {
                            el2 >>= 1;
                            if (valid()) return true;
                        }
                    } while (el2);
                    el2 = el1 >> 1; // don't move the same thing
                    ise2--;
                    if (valid()) return true;
                } while (ise2 >= 0);
                ise2 = 1;
                el1 <<= 1;
                el2 = el1;
                if (valid()) return true;
            } while (el1 < 128);
            el1 = el2 = 1;
            ise1++; ise2 = 1;
            if (valid()) return true;
        } while (ise1 < 2);
        ise1 = 0; ise2 = 1;
        direction += 2;
        if (valid()) return true;
    } while (direction < 3);
    return false;
}

void init() {
    for(move_number = -1, direction = -1, ise1 = 0, ise2 = 1, el1 = el2 = 1; !valid(); next());
   // printf("%i %i %i %i %i\n", direction, ise1, ise2, el1, el2);
}

bool compute_path() {
    // (stack - sp) / 4 is the number of moves needed to achieve state sp
    char valid_idcs[10];
    memset(valid_idcs, -1, 10);
    char valid_idx;

    if ((sp - stack) / 4 == max_steps) // we used all steps to come to here
        return false;
    decode(sp, floors, curr_floor);
    print_state();
    try_end = try_next;
    valid_idx = 0;
    init();
    do {
        if (next_floor == 3) {
            for(t = 0; (t < 6) && !next_floors[t]; t++);
            if (t == 6) return true;
        }
        encode(next_floors, next_floor, encoded);
        for(tsp = stack; (tsp != sp + 4) && memcmp(tsp, encoded, 4); tsp += 4);
        if (tsp != sp + 4) continue; // already been there
        for(tsp = try_next; (tsp != try_end) && memcmp(tsp, encoded, 4); tsp += 5);
        if (tsp != try_end) continue; // already plan going there
        minmo = min_moves(next_floor, next_floors);
//        encode(next_floors, next_floor, encoded, true);
        for(t = valid_idx, tptr = try_end; (tptr != try_next) && (tptr[-1] > minmo); tptr -= 5, t--) {
            memcpy(tptr, tptr - 5, 5);
            valid_idcs[t] = valid_idcs[t - 1];
        }
        memcpy(tptr, encoded, 4);
        tptr[4] = minmo;
        valid_idcs[t] = move_number;
        try_end += 5;
        valid_idx++;
        if (valid_idx >= 10) { printf("too many choices"); exit(1); }
    } while (next());
    
    sp += 4;
    for(valid_idx=0; (valid_idx < 10) && (valid_idcs[valid_idx] >= 0); valid_idx++) {
        decode(sp - 4, floors, curr_floor);
        for(init(); move_number != valid_idcs[valid_idx]; next());
        encode(next_floors, next_floor, sp);
        if (compute_path())
            return true;
    }
    sp -= 4;
    return false;
}

int main() {
    encode(initial, 0, stack);
    sp = stack;
    for(max_steps = min_moves(0, initial); !compute_path(); max_steps++)
    printf("%i\n", max_steps);
}
