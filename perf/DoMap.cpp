#include <iostream>
#include <unordered_map>

#include "Common.h"

int main() {
  std::cout << "Running in Map mode" << std::endl;

  std::unordered_map<int64_t, int64_t> mp {};
  mp.reserve(perf::ITERATIONS);
  for (int64_t c = 0; c <= perf::ITERATIONS; c++) {
    mp[c] = c;
  }

  double sum = 0;
  for (int64_t d = 0; d <= perf::ITERATIONS; d += 2) {
    sum += mp[d];
  }

  std::cout << sum << std::endl;

  return 0;
}
