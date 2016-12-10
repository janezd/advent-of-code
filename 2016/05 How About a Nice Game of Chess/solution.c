#include <stdio.h>
#include <string.h>
#include "openssl/md5.h"


int main() {
    char door_id[] = "ugkcyxxp";
    char try[30], *etry = try + 30, *ptrtry;
    char key[] = "        ", *knext = key;
    unsigned char md5[MD5_DIGEST_LENGTH];

    for(long num = 1, cnum; *knext; cnum=++num) {
        ptrtry = etry;
        while(cnum) {
            *--ptrtry = cnum % 10 + '0';
            cnum /= 10;
        }
        ptrtry -= 8;
        memcpy(ptrtry, door_id, 8);
        MD5((const unsigned char *)ptrtry, etry - ptrtry, md5);
        if (!md5[0] && !md5[1] && !(md5[2] & 0xf0)) {
            *knext++ = (md5[2] < 10 ? 48 : 87) + md5[2]; 
            printf("%s\n", key);
        }
    }
}