#include <string>
#include <iostream>
#include <array>
#include <stdint.h>
#include <stdlib.h>

std::array<uint32_t, 4> get_array();
void print_arr(std::array<uint32_t, 4> *array);

// example of program which works but technically is  incorrect
// as value allocated on stack will disappear
int main(int argc, char* argv[]){
    // this is returned by function
    std::array<uint32_t, 4> v = get_array();
    print_arr(&v);

    return 0;
}

std::array<uint32_t, 4> get_array(){
    // incorrectly allocated on stack and will die after call
    std::array<uint32_t, 4> v2 = {{10, 20, 30, 40}};
    return v2;
}

void print_arr(std::array<uint32_t, 4> *array){
    for(std::array<uint32_t, 4>::iterator it = array->begin(); it != array->end(); ++it){
        std::cout << *it << ", ";
    }
    std::cout << "\n";
}
