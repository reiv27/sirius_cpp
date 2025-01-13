#include <iostream>
#include <string>
#include <cstdint>


int main(int argc, char* argv[]) {

    std::string input = argv[1];

    for (;;) {

        if (input.find('1') != std::string::npos) {
            auto n = input.find('1');
            input.replace(n, 1, "0|");
            continue;
        }
        else if (input.find("|0") != std::string::npos) {
            auto n = input.find("|0");
            input.replace(n, 2, "0||");
            continue;
        }
        else if (input.find('0') != std::string::npos) {
            auto n = input.find('0');
            input.replace(n, 1, "");
            continue;
        }
        else break;
    }

    std::cout << input << std::endl;

    return 0;

}
