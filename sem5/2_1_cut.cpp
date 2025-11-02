#include <iostream>
#include <string>
#include <vector>

static std::vector<size_t> utf8_codepoint_starts(const std::string& s) {
    std::vector<size_t> pos;
    for (size_t i = 0; i < s.size();) {
        pos.push_back(i);
        unsigned char c = (unsigned char)s[i];
        size_t step = (c < 0x80) ? 1 :
                      (c >> 5 == 0x6) ? 2 :
                      (c >> 4 == 0xE) ? 3 :
                      (c >> 3 == 0x1E) ? 4 : 1;
        i += step;
    }
    return pos;
}

std::string truncate_utf8_codepoints(const std::string& s, size_t n) {
    auto starts = utf8_codepoint_starts(s);
    if (starts.size() <= n) return s;
    return s.substr(0, starts[n]) + u8"…";
}

int main() {
    std::string s = "Привет, мир! 😊";

    std::cout << truncate_utf8_codepoints(s, 5) << std::endl;
}