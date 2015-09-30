#define __STDC_FORMAT_MACROS

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char* argv[]){
    // trying some types from C++11
    uint32_t age = 30;

    printf("My age = %d\n", age);
    printf("Max integer = %u\n", UINT32_MAX);

    printf("Let's learn some CPP types\n\n");
    printf("Max uint8_t integer = %u\n", UINT8_MAX);
    printf("Max uint16_t integer = %u\n", UINT16_MAX);
    printf("Max uint32_t integer = %u\n", UINT32_MAX);

    // using macros from here;
    // http://stackoverflow.com/a/9225648/2075157
    // http://en.cppreference.com/w/cpp/types/integer
    printf("Max uint64_t integer = %" PRIu64 "\n", UINT64_MAX);
    


    return 0;
}