#include <string>
#include <iostream>

int main() {
    std::string s = "Привет";
    // std::string_view sv(s.data(), 5);
    std::string s2 = s.substr(0, 5);
    // for (unsigned char ch : s) {
    //     printf("%x\n", ch);
    // }
    std::cout << s2 << std::endl;
    std::cout << s[0] << std::endl;
}