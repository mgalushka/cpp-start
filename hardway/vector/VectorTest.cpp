#include <iostream>

// include cpp becaue we are using templates
#include "Vector.cpp"
#include "gtest/gtest.h"
#include "glog/logging.h"

TEST(VectorUnsafeIteratorTest, unsafe) {
  std::vector<int> v {1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);

  std::vector<int>::iterator it = v.begin();
  it = it + 1;
  EXPECT_EQ(v.size(), 5);
}

TEST(HolderDungling, holder) {
  learning::Holder<int> h(7);
  EXPECT_EQ(*h.begin(), 7);

  // try to mess up with pointer - but actually any pointer returned from function is returned via copy
  // so we are fine - we cannot actually affect original pointer by doing anything with this one
  learning::Holder<int>::iterator it = h.begin();
  it++;
  EXPECT_EQ(*h.begin(), 7);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  return RUN_ALL_TESTS();
}
