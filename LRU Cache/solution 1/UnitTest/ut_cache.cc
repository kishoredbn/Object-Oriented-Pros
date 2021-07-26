#include <gtest/gtest.h>
#include "../cache.h"

#include <memory> 

// Test Fixtures: Evaluated before every Unit Test
class CacheFixtures : public ::testing::Test {
private:
    std::unique_ptr<Cache> cache;

public:
    void SetUp() {
        // code here will execute just before the test is triggered 
        cache = std::make_unique<Cache>(5);
    }

    void TearDown() {
        // code here will execute just after the test is triggered 
        cache = nullptr;
    }

    void CacheSet(int32_t key, int32_t value) {
        if(cache) cache->Set(key, value);
    }

    int32_t CacheGet(int32_t key) {
        if(cache) return cache->Get(key);
        return 0;
    }

};

// Unit-Test 1: 
TEST_F(CacheFixtures, TestCacheCase1) {

    CacheSet(1, 1);
    CacheSet(2, 2);
    CacheSet(3, 3);
    CacheSet(4, 4);
    CacheSet(5, 5);

    EXPECT_EQ(1, CacheGet(1));
    EXPECT_EQ(2, CacheGet(2));
    EXPECT_EQ(3, CacheGet(3));
    EXPECT_EQ(4, CacheGet(4));
    EXPECT_EQ(5, CacheGet(5));
    EXPECT_EQ(0, CacheGet(6));

    CacheSet(6, 6);
    EXPECT_EQ(6, CacheGet(6));
    EXPECT_EQ(0, CacheGet(1));

    CacheSet(1, 1);
    EXPECT_EQ(1, CacheGet(1));
    EXPECT_EQ(0, CacheGet(2));

    CacheSet(2, 2);
    EXPECT_EQ(2, CacheGet(2));
    EXPECT_EQ(0, CacheGet(3));

    CacheSet(3, 3);
    EXPECT_EQ(3, CacheGet(3));
    EXPECT_EQ(0, CacheGet(4));

    CacheSet(4, 4);
    EXPECT_EQ(4, CacheGet(4));
    EXPECT_EQ(0, CacheGet(5));

    CacheSet(5, 5);
    EXPECT_EQ(5, CacheGet(5));
    EXPECT_EQ(0, CacheGet(6));
}

// main() trigger
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}