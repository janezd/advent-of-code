#include <iostream>
#include <sstream>
#include "openssl/md5.h"

int main(int argc, char *argv[]) {
    std::string salt;
    std::cin >> salt;
    unsigned char md5[MD5_DIGEST_LENGTH];
    int sol5 = 0, sol6 = 0;

    for(int i = 1;; i++) {
        std::ostringstream buf;
        buf << salt << i;
        MD5((const unsigned char *)buf.str().c_str(), buf.str().size(), md5);
        if (!md5[0] && !md5[1] && !(md5[2] & 0xf0)) {
            if (!sol5) {
                sol5 = i;
            }
            if (!md5[2]) {
                sol6 = i;
                break;
                }
        }
    }
    std::cout << sol5 << std::endl << sol6 << std::endl;
}
