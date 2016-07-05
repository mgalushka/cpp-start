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
#include <folly/dynamic.h>
#include <folly/json.h>

void print(const folly::dynamic& arr) {
  for (const auto& row : arr) {
      std::cout << row << std::endl;
  }
}

int main(int, char**) {
    auto mergeFields = folly::parseJson("[]");
    print(mergeFields);

    mergeFields = folly::parseJson("[\"some_field0\", \"some_field1\"]");
    print(mergeFields);

    return 0;
}
