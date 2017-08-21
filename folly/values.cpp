#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <folly/Synchronized.h>
#include <unordered_set>

folly::Synchronized<std::unordered_set<std::string>> unorderedMap;

bool return_a() {
  std::cout << "a = " << rand() << std::endl;
  return true;
}

bool return_b() {
  std::cout << "b = " << rand() << std::endl;
  return true;
}

void lock_me_in(const std::string& logType) {
  bool didntExistYet = !unorderedMap.rlock()->count(logType) &&
      unorderedMap.wlock()->insert(logType).second;
  if (didntExistYet) {
    std::cout << "b = " << rand() << std::endl;
  }
}

void lock_me_out(const std::string& logType) {
  bool didntExistYet = !unorderedMap.rlock()->count(logType);
  if (didntExistYet && unorderedMap.wlock()->insert(logType).second) {
    std::cout << "c = " << rand() << std::endl;
  }
}

int main () {

  int a = 0;
  int b = 0;
  int c = 0;

  a == 3 ? b : c = 17;

  std::cout << " a = " << a << std::endl;
  std::cout << " b = " << b << std::endl;
  std::cout << " c = " << c << std::endl;

  std::string log_type("log_Type");

  // std::vector<std::thread> processors_;
  // processors_.reserve(10);
  // for (int i = 0; i < 1; ++i) {
  //   // auto T = std::thread(lock_me_in, log_type);
  //   processors_.push_back(std::thread(lock_me_in, log_type));
  // }
  //
  // for (auto& processorThread : processors_) {
  //   if (processorThread.joinable()) {
  //     processorThread.join();
  //   }
  // }

  auto T = std::thread(lock_me_out, log_type);
  T.join();

  return 0;
}
