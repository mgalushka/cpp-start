#include <string>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

uint32_t* reverse_array(uint32_t length, uint32_t* input);
void print_array(uint32_t length, uint32_t* input);

int main(int argc, char* argv[]){
    std::string str = "This is string";

    std::cout << "Length(" << str << ") = " << str.length() << "\n";

    uint32_t L = 10;
    uint32_t* input = (uint32_t*) malloc(L * sizeof(uint32_t));

    for(uint32_t i = 0; i < L; i++){
        input[i] = 3 * i;
    }

    print_array(L, input);
    input = reverse_array(L, input);
    print_array(L, input);

    free(input);
    return 0;
}

uint32_t* reverse_array(uint32_t length, uint32_t* input){
    if (length <= 1){
        return input;
    }
    uint32_t* result = (uint32_t*) malloc(length * sizeof(uint32_t));
    for (uint32_t i = 0; i < length / 2; i++) {
        result[length - 1 - i] = input[i];
        result[i] = input[length - 1 - i];
    }
    free(input);
    return result;
}

void print_array(uint32_t length, uint32_t* input){
    for (uint32_t i = 0; i < length; i++) {
        std::cout << input[i];
        if (i < (length - 1)){
             std::cout << ", ";
        }
    }
    std::cout << "\n";
}