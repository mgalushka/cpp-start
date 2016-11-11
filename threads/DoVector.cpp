#include <iostream>
#include <vector>

#include "Common.h"

int main() {

  std::cout << "Running in Vector mode" << std::endl;

  std::vector<int64_t> vec {};
  vec.reserve(perf::ITERATIONS);
  for (int64_t c = 0; c <= perf::ITERATIONS; c++) {
    vec.push_back(c);
  }

  double sum = 0;
  for (int64_t d = 0; d <= perf::ITERATIONS; d += 2) {
    sum += vec[d];
  }

  std::cout << sum << std::endl;

  return 0;
}
