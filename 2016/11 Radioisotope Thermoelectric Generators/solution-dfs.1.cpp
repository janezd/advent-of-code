#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char initial[] = {1 + 2 + 32 + 64, 1 + 2 + 32 + 64,
                                4 + 8 + 16,          8 + 16,
                                         0,               4,
                                         0,               0};

#define INVALID(state) ((*(state)) && ((state)[1] & ~*(state)))

// Heuristics that computes the lower bound for the number of moves
unsigned char min_moves(unsigned char floors[8]) {
    unsigned char mfloors[8];
    memcpy(mfloors, floors, 8);
    unsigned char moves = 0;
    for(unsigned char i = 0; i < 3; i++) {
        unsigned char bits = 0, x = mfloors[2 * i];
        for(; x; x >>= 1)
            bits += x & 1;
        x = mfloors[2 * i + 1];
        for(; x; x >>= 1)
            bits += x & 1;
        if (bits > 2)
            moves += 2 * (bits - 2);
        if (bits)
            moves++;
        mfloors[2 * i + 2] |= mfloors[2 * i];
        mfloors[2 * i + 3] |= mfloors[2 * i + 1];
    }
    return moves;
}


// Uniquely (w.r.t. symmetries) encode the position in 4 bytes
void encode(unsigned char floors[8], unsigned char curr_floor, unsigned char encoded[4]) {
    unsigned char transient[8];
    unsigned char fle, flg, fl;
    for(unsigned char bit = 0; bit < 7; bit++) {
        for(fl = 0; fl < 4; fl++) {
            if (floors[2 * fl] & (1 << bit)) flg = fl;
            if (floors[2 * fl + 1] & (1 << bit)) fle = fl;
        }
//        printf("[%i %i; ", flg, fle);
        fle = flg << 2 | fle; 
  //      printf("%i] ", fle);
        for(flg = bit; flg && (transient[flg - 1] > fle); flg--) {
            transient[flg] = transient[flg - 1];
        }
        transient[flg] = fle;
    }
    transient[7] = curr_floor;
//    for(fle = 0; fle < 8; fle++) printf("%i ", transient[fle]);
  //  printf("| ");
    for(fl = 0; fl < 4; fl++) {
        encoded[fl] = transient[2 * fl] + (transient[2 * fl + 1] << 4);
    }
//    printf("Encode: ");
  //  for(fle = 0; fle < 8; fle++) printf("%i ", floors[fle]);
//    printf("-> ");
  //  for(fle = 0; fle < 4; fle++) printf("%i ", encoded[fle]);
    //printf("; %i\n", curr_floor);
}


// Decode the position; decoding is exact up to the symmetry
void decode(unsigned char encoded[4], unsigned char floors[8], unsigned char &curr_floor)
{
    unsigned char bit = 1;
    memset(floors, 0, 8);
    for(unsigned char e = 0; e < 4; e++) {
        unsigned char te = encoded[e];
        floors[2 * ((te >> 2) & 3)] |= bit;
        floors[1 + 2 * (te & 3)] |= bit;        
//        printf("[%i %i %i]\n", (te >> 2) & 3, (te & 3), bit);
        bit <<= 1;
        if (e < 3) {
            floors[2 * (te >> 6)] |= bit;
            floors[1 + 2 * ((te >> 4) & 3)] |= bit;
  //          printf("[%i %i %i]\n", te >> 6, (te >> 4) & 3, bit);
            bit <<= 1;
        }
        else {
            curr_floor = te >> 6;
        }
    }
/*    printf("Decode: ");
    for(bit = 0; bit < 8; bit++) printf("%i ", floors[bit]);
    printf("<- ");
    for(bit = 0; bit < 4; bit++) printf("%i ", encoded[bit]);
    printf("; %i\n", curr_floor);*/
}

// No local variables, so recursion takes as little space as possible
unsigned char max_steps;
unsigned char stack[70 * 4], *sp = stack, *tsp;
unsigned char curr_floor, floors[8], next_floors[8], next_floor, on_this_floor;
unsigned char try_next[10 * 5], *try_end;
unsigned char ise1, el1, ise2, el2, t;
unsigned char next_this, next_next;
unsigned char encoded[4], minmo, valid_move;
unsigned char *tptr;
char direction;

bool compute_path() {
    unsigned char valid_idcs[4];
    char valid_idx;

    if (sp - stack >= max_steps)
        return false;
    decode(sp - 4, floors, curr_floor);

    try_end = try_next;
    valid_move = -1;
    for(direction = -1; direction < 3; direction += 2) {
        if (direction == -1) {
            for(t = 0; (t < curr_floor) && !floors[2 * t] && !floors[2 * t + 1]; t++);
            if (t == curr_floor)
                continue;  // nothing down there
        }
        next_floor = curr_floor + direction;
        if (next_floor > 3)
            continue;
        for(ise1 = 0; ise1 < 2; ise1++) {
            for(el1 = 1; el1 < 128; el1 <<= 1) {
                if (!(floors[2 * curr_floor + ise1] & el1)) {
                    continue;  // no such thing here
                }
                for(ise2 = 0; ise2 < 2; ise2++) {
                    for(el2 = 0; el2 <= el1; el2 = el2 ? el2 << 1 : 1) {
                        if (!ise2 && !el2)
                            continue;  // try empty just once
                        if ((el1 == el2) && (ise1 == ise2))
                            continue; // same thing twice
                        if (el2 && !(floors[2 * curr_floor + ise2] & el2))
                            continue;  // no such thing here
                        if (el2 && (direction == -1))
                            continue;  // don't move two things down
                        memcpy(next_floors, floors, 8);
                        next_floors[2 * curr_floor + ise1] &= ~el1;
                        next_floors[2 * curr_floor + ise2] &= ~el2;
                        if (INVALID(next_floors + 2 * curr_floor)) {
//                            printf("i1 %i %i %i %i\n", el1, ise1, el2, ise2);                      
                            continue;  // can't leave the current floor like this
                        }next_floors[2 * next_floor + ise1] |= el1;
                        next_floors[2 * next_floor + ise2] |= el2;
                        if (INVALID(next_floors + 2 * next_floor)) {
//                            printf("i2 %i %i %i %i\n", el1, ise1, el2, ise2);
                            continue;  // can't have the next floor like this
                        }
                        if (next_floor == 3) {
                            int t = 0;
                            for(; (t < 6) && !next_floors[t]; t++);
                            if (t == 6)
                                return true;
                        }
                        valid_move++;
                        encode(next_floors, next_floor, encoded);
                        for(tsp = stack;
                            (tsp != sp) && 
                            ((tsp[0] != encoded[0]) || (tsp[1] != encoded[1]) ||
                            (tsp[2] != encoded[2]) || (tsp[3] != encoded[3]));
                            tsp += 4);
                        if (tsp != sp)
                            continue;  // already been there
                        for(tsp = try_next;
                            (tsp != try_end) && 
                            ((tsp[0] != encoded[0]) || (tsp[1] != encoded[1]) ||
                            (tsp[2] != encoded[2]) || (tsp[3] != encoded[3]));
                            tsp += 5);
                        if (tsp != try_end)
                            continue; // already plan going there
                        minmo = min_moves(next_floors);
                        for(t = 0, tptr = try_end;
                            (tptr != try_next) && (tptr[-1] < minmo);
                            tptr -= 5, t++) {
                                memcpy(tptr, tptr - 5, 5);
                                valid_idcs[-t] = valid_idcs[-t - 1];
                            }
                        memcpy(tptr, encoded, 4);
                        tptr[4] = minmo;
                        try_end += 5;
                        valid_idcs[-t] = valid_move;
                    }
                }
            }
        }
    }
    if (try_end == try_next)
        return false;
    
    sp += 4;
    for(valid_idx=(try_end - try_next) / 5 - 1; valid_idx >= 0; valid_idx--) {
        printf("%i ", valid_idx);
        // These loops below are "single-shot": at the first recursive call,
        // values are lost, so we need to compute the valid move again
        // The only variables owned by the function are valid_idx and valid_idcs
        for(direction = -1; direction < 3; direction += 2) {
            if (direction == -1) {
                for(t = 0; (t < curr_floor) && !floors[2 * t] && !floors[2 * t + 1]; t++);
                if (t == curr_floor)
                    continue;  // nothing down there
            }
            next_floor = curr_floor + direction;
            if (next_floor > 3)
                continue;
            for(ise1 = 0; ise1 < 2; ise1++) {
                for(el1 = 1; el1 < 128; el1 <<= 1) {
                    if (!(floors[2 * curr_floor + ise1] & el1)) {
                        continue;  // no such thing here
                    }
                    for(ise2 = 0; ise2 < 2; ise2++) {
                        for(el2 = 0; el2 < el1; el2 = el2 ? el2 << 1 : 1) {
                            if (!ise2 && !el2)
                                continue;  // try empty just once
                            if (el2 && !(floors[2 * curr_floor + ise2] & el2))
                                continue;  // no such thing here
                            if (el2 && (direction == -1))
                                continue;  // don't move two things down
                            memcpy(next_floors, floors, 8);
                            next_floors[2 * curr_floor + ise1] ^= el1;
                            next_floors[2 * curr_floor + ise2] ^= el2;
                            if (INVALID(next_floors + 2 * curr_floor))
                                continue;  // can't leave the current floor like this
                            next_floors[2 * next_floor + ise1] |= el1;
                            next_floors[2 * next_floor + ise2] |= el2;
                            if (INVALID(next_floors + 2 * next_floor))
                                continue;  // can't have the next floor like this
                            if (next_floor == 3) {
                                int t = 0;
                                for(; (t < 6) && !next_floors[t]; t++);
                                if (t == 6)
                                    return true;
                            }
                            if(valid_move++ == valid_idcs[valid_idx]) {
                                encode(next_floors, next_floor, encoded);
                                memcpy(sp - 4, tptr, 4);
                                printf("yey");
                                if (compute_path())
                                    return true;
                                // break out of all loops except the outmost
                                direction = 1;
                                ise1 = el1 = ise2 = el2 = 64;
                            }
                        }
                    }
                }
            }
        }
    }
    sp -= 4;
    return false;
}

int main() {
    encode(initial, 0, stack);
    sp = stack + 4;
    for(max_steps = min_moves(initial); !compute_path(); max_steps++)
    printf("%i\n", max_steps);
}
