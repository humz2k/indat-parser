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
```