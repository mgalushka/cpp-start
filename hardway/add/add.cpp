#include <string>
#include <iostream>
#include <array>
#include <cmath>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <algorithm>

#ifdef DEBUG
#else
#define DEBUG false
#endif

using namespace std;

std::string* add(std::string& a, std::string& b);
std::string& reverse(std::string& input);

int main(){
    string a("1");
    string b("1");
    std::cout << *add(a, b) << std::endl;
    //std::cout << add("1", "0") << std::endl;
    //std::cout << add("0", "1") << std::endl;
    //std::cout << add("10", "11") << std::endl;
    //std::cout << add("11", "11") << std::endl;
    //std::cout << add("111", "1111") << std::endl;
    //std::cout << add("1000000000000000000", "1111") << std::endl;
    //std::cout << add("100101010", "101001010") << std::endl;

    std::string input("abcdefgh");
    auto str = reverse(input);

    std::cout << str << std::endl;
    return 0;
}

// add 2 binary strings byte-by-byte
std::string* add(std::string& a, std::string& b) {
    std::string& ar = reverse(a);
    std::string& br = reverse(b);

    uint32_t max_length = std::max(ar.length(), br.length());

    std::string* result = new std::string();
    result->reserve(max_length);

    int carry = 0;
    for(uint32_t i = 0; i < max_length; i++) {
        int ai = 0;
        if (i < ar.length()) {
            ai = static_cast<int>(ar.at(i) - '0');
        }
        int bi = 0;
        if (i < br.length()) {
            bi = static_cast<int>(br.at(i) - '0');
        }

        int sum = (ai + bi + carry);
        int bit = sum % 2;
        carry = static_cast<int>(std::floor(static_cast<double>(sum) / 2));

        if (DEBUG) {
            std::cout << "sum: " << sum << ", bit: " << bit << ", carry: " << carry << std::endl;
        }

        result->insert(0, 1, static_cast<char>(bit + '0'));
    }

    if (carry > 0) {
        if (DEBUG) {
            std::cout << "printing carry" << std::endl;
        }
        result->insert(0, 1, '1');
    }
    
    return result;
}

std::string& reverse(std::string& input) {
    std::reverse(input.begin(), input.end());
    return input;
}