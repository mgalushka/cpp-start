#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    // let's learn a little about std:vector
    std::vector<uint32_t> v;

    for(uint32_t i=0; i< 500; i++){
        v.push_back(i);
    }

    for(std::vector<uint32_t>::iterator it = v.begin(); it != v.end(); ++it){
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    std::map<std::string, std::string> m;
    for(uint32_t i = 0; i < 500; i++){
        m.insert(std::pair<std::string, std::string>(
            std::to_string(i),
            std::to_string(i * i)
        ));
    }

    // find square for some integer saved as std::string
    std::cout << m.find("42")->second << "\n";

    return 0;
}

