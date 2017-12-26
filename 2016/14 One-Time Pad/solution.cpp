#include <stdio.h>
#include <string.h>
#include "openssl/md5.h"

char prev3[1000];
int ptr3 = 0;
char pwd[] = "cuanljph       ";
char *num = pwd + 8;

unsigned char md5[MD5_DIGEST_LENGTH];
int keys[100];
int nkeys = 0;
int maxkey = -1;

char first3() {
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        unsigned char dig = md5[i] & 0xf;
        if ((md5[i] >> 4 == dig) && // same in byte 
            ((i && ((md5[i - 1] & 0xf) == dig)) || // previous is same
             ((i < MD5_DIGEST_LENGTH - 1) && (md5[i + 1] >> 4 == dig)))) {
             return dig;
             }
    }
    return -1;
}

int main() {
    int i, j, k, pptr3;
    for(i = 0;(nkeys < 64) && (i < 30000); i++) {
        sprintf(num, "%i", i);
        MD5((const unsigned char *)pwd, strlen(pwd), md5);
        int handleddigs = 0;
        for(j = 0; j < MD5_DIGEST_LENGTH - 1; j++) {
            if (md5[j] != md5[j + 1])
                continue;
            char dig = md5[j] & 0xf;
            if (handleddigs & (1 << dig))
                continue;
            if ((md5[j] >> 4 != dig) || !((j && ((md5[j-1] & 0xf) == dig)) ||
                                          ((j < MD5_DIGEST_LENGTH - 2) && (md5[j + 2] >> 4 == dig))))
                continue;
            handleddigs |= 1 << dig;
            if (i < 1000) { k = pptr3 = 0; }
            else { k = i - 1000; pptr3 = ptr3; }
            do {
                if (prev3[pptr3] == dig) {
                    keys[nkeys++] = k;
                    printf("%i. %i %i %i\n", nkeys, k, i, dig);
                }
                pptr3 = (pptr3 + 1) % 1000;
                k++;
            } while(pptr3 != ptr3);
        }
        prev3[ptr3] = first3();
        ptr3 = (ptr3 + 1) % 1000;
        if (nkeys >= 64) {
            if (maxkey == -1) {
                for(k = 0; k < nkeys; k++) {
                    if (keys[k] > maxkey) {
                        maxkey = keys[k];
                    }
                }
            }
        }
    }
    for(int i = nkeys; i > 64; i--) {
        for(int j = 0; j < i; j++) {
            if (keys[j] > keys[j + 1]) {
                k = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = k;
            }
        }
    }
    printf("%i\n", keys[63]);
}