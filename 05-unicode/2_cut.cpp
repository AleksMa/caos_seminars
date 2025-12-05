#include <string>
#include <iostream>

int main() {
    std::string s = "Привет, мир! 😊";

    std::string cut = s.substr(0, 5);
    std::cout << cut << std::endl;
}
