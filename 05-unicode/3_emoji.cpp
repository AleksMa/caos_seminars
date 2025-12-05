#include <stdio.h>
#include <string>
#include <iostream>

int main() {

    std::string s = "👩🏻‍🦰";
    // std::string s = "👨‍👩‍👧‍👦";
    // 👨👩‍ 👧‍ 👦 – 16b
    // e2 80 8d – 3 * 3b

    for (unsigned char ch : s) {
        printf("%x\n", ch);
    }
    std::cout << s.size() << " " << s << std::endl;
}