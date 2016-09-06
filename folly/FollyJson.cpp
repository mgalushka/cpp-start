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

const std::string kCountPlaceholder  = "##LINES_COUNT##";

std::string getLineWithCount(std::string originalLine, int32_t counter) {
  // will be replacing including quotes
  int32_t begin = originalLine.find(kCountPlaceholder) - 1;
  if (begin < 0) {
    return originalLine;
  }

  return originalLine.replace(begin,
                              kCountPlaceholder.length() + 2,
                              folly::to<std::string>(counter));
}

int main(int, char**) {
  std::string a("aaaaaI\"##LINES_COUNT##\"Iaaaaaaaaaaaaa");
  std::cout << a.find_first_of(kCountPlaceholder) << std::endl;

  std::cout << "getLineWithCount = "
            << getLineWithCount(a, 1) << std::endl;

  return 0;
}
