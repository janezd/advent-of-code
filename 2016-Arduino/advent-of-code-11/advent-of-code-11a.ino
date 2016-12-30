#include <string.h>
#include "advent.h"

/*
Limitations:
- up to four floors since the floor for an item is coded with two bits
- up to 8 chip-generator pairs since the state of a floor is coded in a single
  byte; this is rather a convenience since this encoding uses constant memory
  w.r.t. the number of moves

- up to MAX_CHOICES possible moves at each state (excluding symmetries)
- up to 2^8 possible moves at each state (including symmetry)
- up to MAX_MOVES moves

In theory, memory consumption is linear in number of moves, n log n in maximal branching
and logarithmic in number of floors. In practice, we need to count bits to pull this of.

ENC_LEN is the number of bytes needed to encode the state (what is where + floor).
It uses half a byte for each chip-generator pair + half a byte per floor. This data
is stored in `stack`, which contains the entire path from the initial to some current
state. `sp` points to the current (deepest) state.

The recursive function uses 1 + MAX_CHOICES log2 (MAX_CHOICES) + call overhead.
The stack needed to retrieve the state uses ENC_LEN bytes (this is essentially
2 bits per item + 2 for floor + rounding)
Hence, the memory that depends on the number of moves is
MAX_MOVES * (1 + MAX_CHOICES log2 (MAX_CHOICES) + PAIRS / 2 + 1 / 2) bytes,
plus MAX_MOVES * call overhead.

In my input for AoC, MAX_MOVES is 61 and MAX_CHOICES is 6, so
61 * (1 + 6 + 4) = 671 bytes + probably 61 * 4 = 244 bytes for calls. Arduino's
memory suffices for that.

1 + MAX_CHOICES log2 (MAX_CHOICES) could be avoided at a cost of traversing all
states everytime from beginning until generating the next state from the state
currently on stack. This would bring the complexity down to
MAX_MOVES * (PAIRS / 2 + 1 / 2 + call overhead), which is some 8 bytes per move.
Each additional pair of items would increase the consumption by half a byte per move.
Furthermore, avoiding recursion at a cost of more complex could would halve this
to four bytes per move.

Another, more time- but less space-efficient soltuion is to reimplement `stack`
so that each call uses as much memory for choices as it actually needs.
*/

#if 0
#define PAIRS 5
unsigned char initial[] = {      1 + 2,  1 + 2,
                           4 +  8 + 16, 8 + 16,
                                     0,      4,
                                     0,      0};
#define HIGHEST_BIT 16
#else
#define PAIRS 7
unsigned char initial[] = {1 + 2 + 32 + 64,  1 + 2 + 32 + 64,
                               4 +  8 + 16,           8 + 16,
                                         0,                4,
                                         0,                0};
#define HIGHEST_BIT 64
#endif

// the first +1 is for encoding floor. The second other +1 is for rounding if #floors is even.
#define ENC_LEN ((PAIRS + 1 + 1) / 2)
// encoded state + number of moves + number of pairs
#define TRY_LEN (ENC_LEN + 2)
#define MAX_CHOICES 6
#define MAX_MOVES 70

// No local variables, so recursion takes as little space as possible
unsigned char max_steps;
unsigned char stack[MAX_MOVES * ENC_LEN], *sp, *tsp;
unsigned char curr_floor, floors[8], next_floors[8], next_floor;
unsigned char try_next[MAX_CHOICES * TRY_LEN], *try_end, *tptr;
unsigned char ise1, el1, ise2, el2, t;
unsigned char encoded[ENC_LEN], minmo, move_number, npairs;
char direction;


#define INVALID(state) ((state)[0] && ((state)[1] & ~(state)[0]))

// Heuristic for the lower bound for the number of moves
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

    // move the elevator (and one item) to the lowest non-empty floor
    for(i = 0; (i < 3) && !floors[2 * i] && !floors[2 * i + 1]; i++);
    mfloors[i] += 1; mfloors[floor] -= 1;
    moves = floor - i;

    // bring everything to the highest floor
    for(i = 0; i < 3; i++) {
        if (mfloors[i] > 2)
            moves += 2 * (mfloors[i] - 2); // bring one thing up, move down again
        if (mfloors[i])
            moves++; // bring the last two (or one)
        mfloors[i + 1] += mfloors[i]; // everything is now one floor higher
    }
    return moves;
}

char pairs(unsigned char floors[8]) {
    char m = 0;
    for(char floor = 0; floor < 4; floor++)
        for(unsigned char both = floors[2 * floor] & floors[2 * floor + 1]; both; both >>= 1)
            m += both & 1;
    return m;
}


// Uniquely (w.r.t. symmetries) encode the position in ENC_LEN bytes
void encode(unsigned char floors[8], unsigned char floor, unsigned char encoded[ENC_LEN]) {
    unsigned char transient[PAIRS + 1];
    unsigned char fle, flg, fl;
    for(unsigned char bit = 0; bit < PAIRS; bit++) {
        for(fl = 0; fl < 4; fl++) {
            if (floors[2 * fl] & (1 << bit)) flg = fl;
            if (floors[2 * fl + 1] & (1 << bit)) fle = fl;
        }
        fle = flg << 2 | fle;
        // insertion sort
        for(flg = bit; flg && (transient[flg - 1] < fle); flg--) {
            transient[flg] = transient[flg - 1];
        }
        transient[flg] = fle;
    }
    transient[PAIRS] = floor;
    for(fl = 0; fl < ENC_LEN; fl++) {
        encoded[fl] = transient[2 * fl] + (transient[2 * fl + 1] << 4);
    }
}


// Decode the position; decoding is exact up to the symmetry
void decode(unsigned char encoded[ENC_LEN], unsigned char floors[8], unsigned char &floor)
{
    unsigned char bit = 1;
    memset(floors, 0, 8);
    for(unsigned char e = 0; e < ENC_LEN; e++) {
        unsigned char te = encoded[e];
        floors[2 * ((te >> 2) & 3)] |= bit;
        floors[1 + 2 * (te & 3)] |= bit;        
        bit <<= 1;
        // this works only for odd number of pairs
        if (e < ENC_LEN - 1) {
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

    if ((el2 > el1) || (el1 > HIGHEST_BIT) || (ise2 > 1) || (ise1 > 1) || (direction == -3) ||
        (!ise2 && !el2) || // try empty just once
        ((el2 == el1) && (ise2 == ise1)) || // move same thing twice
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
                        el2 = el2 ? el2 << 1 : 1;
                        if (valid()) return true;
                    } while (el2 <= el1);
                    el2 = 0;
                    ise2++;
                    if (valid()) return true;
                } while (ise2 < 2);
                ise2 = 0;
                el1 <<= 1;
                if (valid()) return true;
            } while (el1 <= HIGHEST_BIT);
            el1 = 1;
            ise1++;
            if (valid()) return true;
        } while (ise1 < 2);
        ise1 = 0;
        direction -= 2;
        if (valid()) return true;
    } while (direction > -3);
    return false;
}

void init_moves() {
    for(move_number = -1, direction = 1, ise1 = ise2 = 0, el1 = 1, el2 = 0; !valid(); next());
}

bool compute_path() {
    // (stack - sp) / ENC_LEN is the number of moves needed to achieve state sp
    char valid_idcs[MAX_CHOICES];
    memset(valid_idcs, -1, MAX_CHOICES);
    char valid_idx;

    if ((sp - stack) / ENC_LEN == max_steps) // we used all steps to come to here
        return false;
    showNumber((sp - stack) / ENC_LEN, 0);
    tone(2, 400 + 2 * int(sp - stack), 50);
    decode(sp, floors, curr_floor);
    if ((sp - stack) / ENC_LEN + min_moves(curr_floor, floors) > max_steps)
        return false;
    try_end = try_next;
    valid_idx = 0;
    init_moves();
    do {
        if (next_floor == 3) {
            for(t = 0; (t < 6) && !next_floors[t]; t++);
            if (t == 6) return true;
        }
        encode(next_floors, next_floor, encoded);
        for(tsp = stack; (tsp != sp + ENC_LEN) && memcmp(tsp, encoded, ENC_LEN); tsp += ENC_LEN);
        if (tsp != sp + ENC_LEN) continue; // already been there
        for(tsp = try_next; (tsp != try_end) && memcmp(tsp, encoded, ENC_LEN); tsp += TRY_LEN);
        if (tsp != try_end) continue; // already plan going there
        minmo = min_moves(next_floor, next_floors);
        npairs = pairs(next_floors);
        for(t = valid_idx, tptr = try_end;
            ((tptr != try_next) && (tptr[-2] > minmo)) || ((tptr[-2] == minmo) && (tptr[-1] < npairs));
            tptr -= TRY_LEN, t--) {
                memcpy(tptr, tptr - TRY_LEN, TRY_LEN);
                valid_idcs[t] = valid_idcs[t - 1];
        }
        memcpy(tptr, encoded, ENC_LEN);
        tptr[ENC_LEN] = minmo;
        tptr[ENC_LEN + 1] = npairs;
        valid_idcs[t] = move_number;
        try_end += TRY_LEN;
        valid_idx++;
        if (valid_idx == MAX_CHOICES) { showNumber(9999, 4); showNumber(9999, 0); tone(2, 500, 100); }
    } while (next());
    
    sp += ENC_LEN;
    for(valid_idx=0; (valid_idx < MAX_CHOICES) && (valid_idcs[valid_idx] >= 0); valid_idx++) {
        decode(sp - ENC_LEN, floors, curr_floor);
        for(init_moves(); move_number != valid_idcs[valid_idx]; next());
        encode(next_floors, next_floor, sp);
        if (compute_path())
            return true;
    }
    sp -= ENC_LEN;
    return false;
}

void setup() {
    pinMode(2, OUTPUT);
    
    encode(initial, 0, stack);
    sp = stack;
    for(max_steps = min_moves(0, initial); !compute_path(); max_steps++);
    showNumber(max_steps, 0);
}

void loop() {}
