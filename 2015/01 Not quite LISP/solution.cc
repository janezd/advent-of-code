#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
   std::string s;
   std::cin >> s;
   int f = 0, b = -1;
   for(std::string::const_iterator si(s.begin()), se(s.end()); si != se; si++) {
       if (*si == '(') f++;
       if ((*si == ')') && (--f < 0) && (b < 0)) b = si - s.begin() + 1;
   }
   std::cout << f << "\n" << b << "\n";
}
