#include "indat-parser.hpp"

#include <iostream>
#include <vector>
#include <string>

int main() {
    indat::Parser parser("example.params");
    std::cout << parser.get<double>("MY_DOUBLE_PARAM") << std::endl;
    std::cout << parser.get<int>("MY_INT_PARAM") << std::endl;
    std::cout << parser.get<std::string>("MY_STRING_PARAM") << std::endl;

    for (auto i : parser.get<std::vector<int>>("MY_INT_LIST")) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto i : parser.get<std::vector<double>>("MY_DOUBLE_LIST")) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto i : parser.get<std::vector<std::string>>("MY_STRING_LIST")) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}