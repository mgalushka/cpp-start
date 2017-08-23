#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <folly/Checksum.h>
#include <folly/Synchronized.h>
#include <boost/crc.hpp>
#include <unordered_set>

uint32_t boost_crc32(const std::string& data) {
  boost::crc_32_type result;
  result.process_bytes(data.c_str(), data.length());
  return result.checksum();
}

uint32_t folly_crc32(const std::string& data) {
  return ~folly::crc32(reinterpret_cast<const uint8_t*>(data.c_str()), data.length());
}

int main () {
  std::srand(std::time(0));
  for (int t=0; t<=100000; t++) {
    int32_t a = std::rand();

    auto str = std::to_string(a);
    auto x = boost_crc32(str);
    auto y = folly_crc32(str);

    if (x != y) {
      std::cout << str << std::endl;
      std::cout << x << std::endl;
      std::cout << y << std::endl;
      break;
    }
  }
}
