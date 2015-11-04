#include <iostream>

#include "gtest/gtest.h"
#include "glog/logging.h"

#include "Change.h"
#include "Money.h"

TEST(MoneyTest, equals) {
  EXPECT_EQ(change::Money(123, 44), change::Money(123, 44));

  change::Money m1 {123, 44};
  change::Money m2 {123, 45};
  EXPECT_FALSE(m1 == m2);
  EXPECT_TRUE(m1 != m2);

  change::Money m(1, 2);
  m = change::Money(2, 3);
  ASSERT_EQ(change::Money(2, 3), m);

}

TEST(MoneyTest, comparisons) {
  ASSERT_LT(change::Money(10, 99), change::Money(11, 10));
  ASSERT_LE(change::Money(10, 99), change::Money(11, 10));
  ASSERT_EQ(change::Money(10, 99), change::Money(10, 99));
  ASSERT_LE(change::Money(10, 99), change::Money(10, 99));
  ASSERT_GE(change::Money(10, 99), change::Money(10, 99));
  ASSERT_GT(change::Money(11, 00), change::Money(10, 99));
  ASSERT_GE(change::Money(11, 00), change::Money(10, 99));

  EXPECT_TRUE(change::Money(10, 99) < change::Money(11, 10));
  EXPECT_TRUE(change::Money(10, 99) <= change::Money(11, 10));
  EXPECT_TRUE(change::Money(10, 99) == change::Money(10, 99));
  EXPECT_TRUE(change::Money(10, 99) <= change::Money(10, 99));
  EXPECT_TRUE(change::Money(10, 99) >= change::Money(10, 99));
  EXPECT_TRUE(change::Money(11, 00) > change::Money(10, 99));
  EXPECT_TRUE(change::Money(11, 00) >= change::Money(10, 99)); 
}

TEST(MoneyTest, arithmetic) {
  change::Money m(10, 50);
  change::Money add(1, 55);

  change::Money sum0 = m + add;
  ASSERT_EQ(change::Money(12, 5), sum0);

  change::Money diff0 = m - add;
  ASSERT_EQ(change::Money(8, 95), diff0);

  change::Money diff(7, 40);
  ASSERT_EQ(m - add - add, diff);
  ASSERT_EQ(m - add, diff + add);

  diff += change::Money(1, 50);
  ASSERT_EQ(change::Money(8, 90), diff);

  diff -= change::Money(3, 60);
  ASSERT_EQ(change::Money(5, 30), diff);
}

TEST(MoneyTest, multiplication) {
  change::Money m(10, 50);
  ASSERT_EQ(change::Money(73, 50), m * 7);
  ASSERT_EQ(change::Money(10, 50), m * 1);
  ASSERT_EQ(change::Money(0, 0), m * 0);
  ASSERT_EQ(change::Money(7350, 0), m * 700);
}

TEST(MoneyTest, division) {
  change::Money m(9, 90);
  ASSERT_THROW(m / 0, std::invalid_argument);
  ASSERT_EQ(change::Money(3, 30), m / 3);
  ASSERT_EQ(change::Money(2, 47), m / 4);
  ASSERT_EQ(change::Money(1, 98), m / 5);
}

TEST(ChangeTest, change) {
  ASSERT_THROW(change::getChange(change::Money(10, 5), change::Money(9, 5)), std::runtime_error);
  ASSERT_EQ(change::Money(1, 0), change::getChange(change::Money(10, 5), change::Money(11, 5)));
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  return RUN_ALL_TESTS();
}
