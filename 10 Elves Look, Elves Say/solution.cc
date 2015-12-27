#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

int main(int argc, char *argv[]) {
    std::string s("1113222113");
    for(int i = 0; i < 50; ) {
        std::stringstream n;
        for(std::string::const_iterator p(s.begin()), b; p != s.end(); p = b) {
            for(b = p; (b != s.end()) && (*b == *p); b++);
            n << (b - p) << *p;
        }
        s = n.str();
        if (++i % 10 == 0) {
            std::cout << i << ": " << s.size() << std::endl;
        }
    }
}
