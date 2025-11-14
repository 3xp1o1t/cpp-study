#include <gtest/gtest.h>
#include <vector>

TEST(SampleTest, VectorBasics) {
  std::vector<int> v{1,2,3};
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
}
