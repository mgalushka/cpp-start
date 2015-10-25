#include <iostream>
#include "Median.h"
#include "gtest/gtest.h"
#include "glog/logging.h"

namespace std {

  template <class T>
  std::ostream& operator<<(std::ostream& o, const std::vector<T>& v) {
    for (auto i : v) {
      o << i << ", ";
    }
    o << "\n";
    return o;
  }
};

TEST(MedianEasy, sanity) {
  std::vector<int> v;

  ASSERT_THROW(median::median(v), std::runtime_error);

  v.push_back(1);
  EXPECT_EQ(median::median(v), 1);

  v.push_back(2);
  EXPECT_EQ(median::median(v), 1);

  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }

  EXPECT_EQ(median::median(v), 2);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  return RUN_ALL_TESTS();
}
