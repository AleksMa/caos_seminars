#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <cstring>

int main() {
    // std::setlocale(LC_ALL, "en_US.UTF-8");

    std::string utf8 = "Привет, мир! 😊";

    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wide = conv.from_bytes(utf8);

    // std::wcout << L"Оригинал: " << wide << L"\n";
    // std::wcout << L"Длина в wchar_t: " << wide.size() << L"\n";

    std::wstring cut = wide.substr(0, 5);
    // std::wcout << L"Обрезка: " << cut << L"…\n";

    std::string back = conv.to_bytes(cut);
    const char* cs = back.c_str();
    std::cout << "UTF-8 обратно: " << cs << " " << strlen(cs) << "\n";
    // std::cout << "UTF-8 обратно: " << back << " " << back.size() << "\n";
}
