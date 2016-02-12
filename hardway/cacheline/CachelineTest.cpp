#include <folly/detail/CacheLocality.h>

#include "gtest/gtest.h"
#include "glog/logging.h"

namespace cacheline {
    //folly::AtomicBitSet<1> abs;
}

TEST(PrimitiveTest, primitive) {
    EXPECT_EQ(1 + 1, 2);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  return RUN_ALL_TESTS();
}