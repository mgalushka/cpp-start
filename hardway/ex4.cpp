#include <string>
#include <iostream>
#include <array>
#include <stdint.h>
#include <stdlib.h>

void print_arr(std::array<uint32_t, 4> *array);

int main(int argc, char* argv[]){
    // this is allocated on heap
    std::array<uint32_t, 4> *v = new std::array<uint32_t, 4>;

    for(int i = 0; i < 4; i++){
        (*v)[i] = i;
    }
    print_arr(v);

    delete v;

    // this is allocated on stack - so not needed to clean memory
    std::array<uint32_t, 4> v2 = {{10, 20, 30, 40}};
    print_arr(&v2);
    return 0;
}

void print_arr(std::array<uint32_t, 4> *array){
    for(std::array<uint32_t, 4>::iterator it = array->begin(); it != array->end(); ++it){
        std::cout << *it << ", ";
    }
    std::cout << "\n";
}
