#include <fenv.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <map>
#include <tuple>
#include <thread>
#include <chrono>
#include <mutex>

#include <folly/Conv.h>

void convertToInt(const std::string& input) {
    try {
        int64_t value = folly::to<int64_t>(input);
        std::cout << "Converted to int64_t: \"" << input << "\" successfully: " << value << std::endl;
    } catch (const std::range_error& e){
        std::cout << e.what() <<std::endl;
    }
}

int main(int, char**) {
    std::cout << "Hello world folly" << std::endl;

    convertToInt("77");
    convertToInt("77 ");
    convertToInt(" 77 ");
    convertToInt("77 a");
    convertToInt("77 x");
    convertToInt("77");
    convertToInt("abc");
    convertToInt("");
    convertToInt("0x0");
    convertToInt("0.000000");

    return 0;
}