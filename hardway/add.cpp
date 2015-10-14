#include <string>
#include <iostream>
#include <array>
#include <stdint.h>
#include <stdlib.h>
#include <string>

std::string add(std::string a, std::string b);

int main(){
    std::cout << add("100101010", "101001010") << std::endl;
    return 0;
}

// add 2 binary strings byte-by-byte
std::string add(std::string a, std::string b) {
    for(auto ait = end(a); ait != begin(a); ait--) {
        std::cout << *ait << std::endl;
    }
    for(auto bit = end(b); bit != begin(b); bit--) {
        std::cout << *bit << std::endl;
    }
    return "";
}
