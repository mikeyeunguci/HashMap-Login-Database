// HashMapTests.cpp
//
// ICS 45C Spring 2022
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided a few tests
// already, though I've commented them out, because they won't compile and
// link until you've implemented some things.
//
// Of course, you'll want to write lots more of these tests yourself, because
// this is an inexpensive way to know whether things are working the way
// you expect -- including scenarios that you won't happen to hit in the
// course of testing your overall program.  (You might also want to be sure
// that your HashMap implementation is complete and correct before you try
// to write the rest of the program around it, anyway; there's a very
// substantial amount of partial credit available if all that works is
// HashMap.)

#include <gtest/gtest.h>
#include "HashMap.hpp"


TEST(HashMapTests, sizeOfNewlyCreatedHashMapIsZero)
{
    HashMap empty;
    ASSERT_EQ(0, empty.size());
}


TEST(HashMapTests, emptyMapContainsNoKeys)
{
    HashMap empty;
    ASSERT_FALSE(empty.contains("first"));
    ASSERT_FALSE(empty.contains("second"));
}


TEST(HashMapTests, containKeyAfterAddingIt)
{
    HashMap hm;
    hm.add("Boo", "perfect");
    ASSERT_TRUE(hm.contains("Boo"));
}


TEST(HashMapTests, containKeyAfterAddingWithLambdahashFunction)
{
    HashMap hm1{[](const std::string& s) { return 0; }};
    hm1.add("Boo", "perfect");
    ASSERT_TRUE(hm1.contains("Boo"));
}


namespace
{
    unsigned int someHashFunction(const std::string& s)
    {
        return 19;
    }
}


TEST(HashMapTests, containKeyafterConstructWithFunction)
{
    HashMap hm1{someHashFunction};
    hm1.add("Boo", "perfect");
    ASSERT_TRUE(hm1.contains("Boo"));
}


TEST(HashMapTests, containKeyAfterAssignOperatorAfterConstructwithFunction)
{
    HashMap hm1{someHashFunction};
    HashMap hm2;
    hm1.add("Boo", "Thornton");
    hm2.add("Mike", "pass123");
    hm2.add("MikeYeung", "pass123");
    hm2.add("JikeYeung", "password");
    hm1 = hm2;
    EXPECT_TRUE(hm1.contains("Mike"));
    EXPECT_TRUE(hm1.contains("MikeYeung"));
    EXPECT_TRUE(hm1.contains("JikeYeung"));
    EXPECT_FALSE(hm1.contains("Boo"));
    hm1.add("test", "pass");
    EXPECT_FALSE(hm2.contains("test"));
}


namespace
{
    void takesHashMapByValue(HashMap hm)
    {
        hm.add("Mike", "pass123");
        EXPECT_TRUE(hm.contains("Mike"));
        EXPECT_TRUE(hm.contains("Mikey"));
    }
}


TEST(HashMapTests, containNewKeyAfterPassbyVal)
{
    HashMap hm1;
    hm1.add("Mikey", "yeung");
    takesHashMapByValue(hm1);
    EXPECT_FALSE(hm1.contains("Mike"));
}


TEST(HashMapTests, containKeyAfterCopyConstructor)
{
    HashMap hm1;
    HashMap hm2;
    hm2.add("Mike", "pass123");
    hm2.add("MikeYeung", "pass123");
    hm2.add("JikeYeung", "password");
    hm1 = hm2;
    EXPECT_TRUE(hm1.contains("Mike"));
    EXPECT_TRUE(hm1.contains("MikeYeung"));
    EXPECT_TRUE(hm1.contains("JikeYeung"));
    EXPECT_FALSE(hm1.contains("Boo"));
    hm1.add("test", "pass");
    EXPECT_FALSE(hm2.contains("test"));
    EXPECT_EQ(4, hm1.size());
}


TEST(HashMapTests, containKeyAfterAssignOperator)
{
    HashMap hm1;
    HashMap hm2;
    hm1.add("Boo", "Thornton");
    hm2.add("Mike", "pass123");
    hm2.add("MikeYeung", "pass123");
    hm2.add("JikeYeung", "password");
    hm1 = hm2;
    EXPECT_TRUE(hm1.contains("Mike"));
    EXPECT_TRUE(hm1.contains("MikeYeung"));
    EXPECT_TRUE(hm1.contains("JikeYeung"));
    EXPECT_FALSE(hm1.contains("Boo"));
    hm1.add("test", "pass");
    EXPECT_FALSE(hm2.contains("test"));
    EXPECT_EQ(4, hm1.size());
}


TEST(HashMapTests, RemoveKeyAfterAddingIt)
{
    HashMap hm;
    hm.add("Boo", "perfect");
    ASSERT_EQ(1, hm.size());
    ASSERT_TRUE(hm.remove("Boo"));
    ASSERT_EQ(0, hm.size());
}


TEST(HashMapTests, RemoveNonExistentKey)
{
    HashMap hm;
    hm.add("Boo", "perfect");
    ASSERT_FALSE(hm.remove("Mike"));
    ASSERT_EQ(1, hm.size());
}


TEST(HashMapTests, GetValueAssociatedWithKey)
{
    HashMap hm1;
    hm1.add("Boo", "perfect");
    std::string key{"Boo"};
    std::string value = hm1.value(key);
    ASSERT_EQ("perfect", value);
}


TEST(HashMapTests, GetValueAssociatedWithNonExistentKey)
{
    HashMap hm1;
    hm1.add("Boo", "perfect");
    std::string key{"Mike"};
    std::string value = hm1.value(key);
    ASSERT_EQ("", value);
}


TEST(HashMapTests, GetSize)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    ASSERT_EQ(3, hm.size());
}


TEST(HashMapTests, GetBucketCount)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    ASSERT_EQ(10, hm.bucketCount());
}


TEST(HashMapTests, GetLoadFactor)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    ASSERT_EQ(0.3, hm.loadFactor());
}


TEST(HashMapTests, GetMaxBucketSize)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    hm.add("MikeYeung", "password123");
    hm.add("superman", "something");
    hm.add("wandavision", "dr strange");
    hm.add("dr strange", "somepass");
    hm.add("hello world", "yay");
    ASSERT_EQ(2, hm.maxBucketSize());
}


TEST(HashMapTests, correctCapForReHash)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    hm.add("JikeYeung", "password123");
    hm.add("Ike", "pass123");
    hm.add("Superman", "pass1234");
    hm.add("Yucy", "perfect");
    hm.add("Michael", "password123");
    hm.add("Jose", "randompass");
    ASSERT_EQ(21, hm.bucketCount());
}


TEST(HashMapTests, correctSzForReHash)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    hm.add("JikeYeung", "password123");
    hm.add("Ike", "pass123");
    hm.add("Superman", "pass1234");
    hm.add("Yucy", "perfect");
    hm.add("Michael", "password123");
    hm.add("Jose", "randompass");
    ASSERT_EQ(9, hm.size());
}


TEST(HashMapTests, containKeyAfterReHash)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    hm.add("JikeYeung", "password123");
    hm.add("Ike", "pass123");
    hm.add("Superman", "pass1234");
    hm.add("Yucy", "perfect");
    hm.add("Michael", "password123");
    hm.add("Jose", "randompass");
    EXPECT_TRUE(hm.contains("Mike"));
    EXPECT_TRUE(hm.contains("Spiderman"));
    EXPECT_TRUE(hm.contains("Boo"));
    EXPECT_TRUE(hm.contains("JikeYeung"));
    EXPECT_TRUE(hm.contains("Ike"));
    EXPECT_TRUE(hm.contains("Superman"));
    EXPECT_TRUE(hm.contains("Yucy"));
    EXPECT_TRUE(hm.contains("Michael"));
    EXPECT_TRUE(hm.contains("Jose"));
}


TEST(HashMapTests, containKeyAfterClear)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    hm.add("JikeYeung", "password123");
    hm.add("Ike", "pass123");
    hm.add("Superman", "pass1234");
    hm.add("Yucy", "perfect");
    hm.add("Michael", "password123");
    hm.add("Jose", "randompass");
    hm.clear();
    ASSERT_FALSE(hm.contains("Michael"));
}


TEST(HashMapTests, correctSizeAfterClear)
{
    HashMap hm;
    hm.add("Mike", "pass123");
    hm.add("Spiderman", "pass1234");
    hm.add("Boo", "perfect");
    hm.add("JikeYeung", "password123");
    hm.add("Ike", "pass123");
    hm.add("Superman", "pass1234");
    hm.add("Yucy", "perfect");
    hm.add("Michael", "password123");
    hm.add("Jose", "randompass");
    hm.clear();
    ASSERT_EQ(0, hm.size());
}




