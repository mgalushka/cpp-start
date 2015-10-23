#include "Nearest.h"
#include "gtest/gtest.h"
#include "glog/logging.h"
#include <algorithm>

using namespace std;
using namespace nearest;


// check sizes
TEST(NearestEasy, sanity) {
  vector<Point> v;
  // empty
  EXPECT_EQ(nearestN(v, 5).size(), 0);

  // 1
  v.push_back({1.0, 1.0, 1.0});
  EXPECT_EQ(nearestN(v, 5).size(), 1);

  // 2
  v.push_back({2.0, 2.0, 2.0});
  EXPECT_EQ(nearestN(v, 5).size(), 2);

  // 5
  for (int i = 0; i < 5; i++) {
    auto d = static_cast<double>(i);
    v.push_back({d,d,d});
  }
  EXPECT_EQ(nearestN(v, 5).size(), 5);
  EXPECT_EQ(nearestN(v, 0).size(), 0);
}

// real examples
TEST(NearestEasy, some_examples) {
  vector<Point> v;
  for (int i=0; i<100; i++) {
    auto d = static_cast<double>(i);
    v.push_back({d,d,d});
  }
  vector<Point> ordered = v;
  std::random_shuffle(v.begin(), v.end());
  auto sample = nearestN(v, 5);
  ASSERT_EQ(sample.size(), 5);
  EXPECT_TRUE(sample[0] == ordered[0]);
  EXPECT_TRUE(sample[1] == ordered[1]);
  EXPECT_TRUE(sample[2] == ordered[2]);
  EXPECT_TRUE(sample[3] == ordered[3]);
  EXPECT_TRUE(sample[4] == ordered[4]);
}

TEST(NearestHard, test) {
  vector<Point> v;
  for (int i=0; i<100; i++) {
    auto d = static_cast<double>(i);
    v.push_back({d,d,d});
  }
  vector<Point> ordered = v;
  std::random_shuffle(v.begin(), v.end());

  // test origin point
  auto sample = nearestN(v, 5, {0,0,0}, 9999999.0);
  ASSERT_EQ(sample.size(), 5);
  EXPECT_TRUE(sample[0] == ordered[0]);
  EXPECT_TRUE(sample[1] == ordered[1]);
  EXPECT_TRUE(sample[2] == ordered[2]);
  EXPECT_TRUE(sample[3] == ordered[3]);
  EXPECT_TRUE(sample[4] == ordered[4]);

  // test real reference point
  auto test_ref = nearestN(v, 5, {0.9, 0.9, 0.9}, 9999999.0);
  ASSERT_EQ(test_ref.size(), 5);
  EXPECT_TRUE(test_ref[0] == ordered[1]);
  EXPECT_TRUE(test_ref[1] == ordered[0]);
  EXPECT_TRUE(test_ref[2] == ordered[2]);
  EXPECT_TRUE(test_ref[3] == ordered[3]);
  EXPECT_TRUE(test_ref[4] == ordered[4]);

  // test threshold
  auto test_dist = nearestN(v, 5, {0.9, 0.9, 0.9}, 3.0);
  ASSERT_EQ(test_dist.size(), 3);
  EXPECT_TRUE(test_dist[0] == ordered[1]);
  EXPECT_TRUE(test_dist[1] == ordered[0]);
  EXPECT_TRUE(test_dist[2] == ordered[2]);

  // test 0 distance
  auto test_0dist = nearestN(v, 5, {0.9, 0.9, 0.9}, 0.0);
  ASSERT_EQ(test_0dist.size(), 0);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  return RUN_ALL_TESTS();
}
