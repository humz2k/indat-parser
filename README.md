# indat-parser

C++17 parser for [HACC](https://cpac.hep.anl.gov/projects/hacc/) style params files.

## Example

### `example.params`
```
# This is a comment

# single value parameters
MY_DOUBLE_PARAM 1.4
MY_INT_PARAM 101
MY_STRING_PARAM test

# list parameters
MY_INT_LIST 1 2 3 4 5
MY_DOUBLE_LIST 1.2 1.3 1.4
MY_STRING_LIST a bb ccc dddd eeeee
```
### `example.cpp`
```c++
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
```