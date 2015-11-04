#include <iostream>
#include "gtest/gtest.h"
#include "glog/logging.h"

TEST(MoneyTest, fist) {
  EXPECT_EQ(1, 1);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  return RUN_ALL_TESTS();
}
