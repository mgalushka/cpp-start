#include <iostream>
#include <map>
#include <unordered_map>

namespace temp_copy {

    std::map<int, int> globalMap {std::pair<int, int>(0, 0), std::pair<int, int>(1, 1)};
    std::unordered_map<int, int> globalUnorderedMap {std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};

}

// this is just for test purposes - print in maps
template <class K, class V>
std::ostream& operator<<(std::ostream& os, std::map<K, V>& _map)  {
    for(auto const &pair : _map) {
        os << "[" << pair.first << " => " << pair.second << "]\n";
    }
    return os;
}

template <class K, class V>
std::ostream& operator<<(std::ostream& os, std::unordered_map<K, V>& _map)  {
    for(auto const &pair : _map) {
        os << "[" << pair.first << " => " << pair.second << "]\n";
    }
    return os;
}

int main(){
    std::cout << "Map:\n" << temp_copy::globalMap << std::endl;
    std::cout << "Unrdered map:\n" << temp_copy::globalUnorderedMap << std::endl;

    // start mangling with local copies
    std::map<int, int> local1;
    local1 = temp_copy::globalMap;
    local1.insert(std::pair<int, int>(7, 7));


    std::cout << "Local copy (new line):\n" << local1 << std::endl;
    std::cout << "Map (new line):\n" << temp_copy::globalMap << std::endl;

    std::map<int, int> local2 = temp_copy::globalMap;
    local2.insert(std::pair<int, int>(7, 7));

    std::cout << "Local copy (same line):\n" << local2 << std::endl;
    std::cout << "Map (new line):\n" << temp_copy::globalMap << std::endl;

    return 0;
}