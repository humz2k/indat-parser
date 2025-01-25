#include "indat-parser.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
    indat::Parser parser("example.params");

    std::cout << parser.get<double>("MY_DOUBLE_PARAM").value_or(0) << std::endl;
    std::cout << parser.get<int>("MY_INT_PARAM").value_or(0) << std::endl;
    std::cout << parser.get<std::string>("MY_STRING_PARAM").value_or("")
              << std::endl;

    for (auto i : parser.get<std::vector<int>>("MY_INT_LIST")
                      .value_or(std::vector<int>{})) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto i : parser.get<std::vector<double>>("MY_DOUBLE_LIST")
                      .value_or(std::vector<double>{})) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto i : parser.get<std::vector<std::string>>("MY_STRING_LIST")
                      .value_or(std::vector<std::string>{})) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}