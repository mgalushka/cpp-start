#include <string>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    // let's learn what is pointer
    uint32_t num = 10;
    uint32_t* pnum = &num;

    std::cout << num << "\n";
    std::cout << *pnum << "\n";

    // dinamic allocation with new operator
    uint32_t* nint = new uint32_t;

    // set value with - dereference operator *
    *nint = 1234;
    std::cout << *nint << "\n";

    delete nint;

    return 0;
}
