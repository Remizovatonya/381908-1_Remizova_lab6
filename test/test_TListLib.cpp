#include "TList.h"
#include "../gtest/gtest.h"

TEST(TestSuite, can_create_list)
{
    ASSERT_NO_THROW(TList<int>c);
}

TEST(List, can_push_item_to_list)
{
    TList<int>c(10);
    ASSERT_NO_THROW(c.InsFirst(1));
}

TEST(List, can_push_item_to_list_back)
{
    TList<int>c(11);
    for (int i = 0; i < 10; ++i) {
        c.InsFirst(i);
    }
    ASSERT_NO_THROW(c.InsLast(1));
}

TEST(List, can_get_iterator)
{
    TList<int>c(10);
    for (int i = 0; i < 10; ++i) {
        c.InsFirst(i);
    }
    ASSERT_NO_THROW(c.begin());
}

TEST(List, can_iterate_list)
{
    TList<int>c(10);
    for (int i = 0; i < 10; ++i) {
        c.InsLast(i);
    }
    TList<int>::iterator iter = c.begin();
    for (int j = 0; j < 10; ++j) {
        EXPECT_EQ(*iter, j);
        iter++;
    }
}

TEST(List, can_copy_list)
{
    TList<int>c(10);
    for (int i = 0; i < 10; ++i) {
        c.InsLast(i);
    }

    TList<int>b = c;
    TList<int>::iterator iter = b.begin();
    for (int j = 0; j < 10; ++j) {
        EXPECT_EQ(*iter, j);
        iter++;
    }
}

TEST(List, default_list_is_empty)
{
    TList<int>c(10);
    EXPECT_EQ(c.IsEmpty(), true);
}

TEST(List, can_delete_items)
{
    TList<int>c(10);
    for (int i = 0; i < 10; ++i) {
        c.InsLast(i);
    }

    for (int j = 0; j < 10; ++j) {
        c.DelFirst();
    }
    EXPECT_EQ(c.IsEmpty(), true);
}

TEST(List, can_get_first_elem)
{
    TList<int>c(10);
    for (int i = 0; i < 10; ++i) {
        c.InsLast(i);
    }
    int data = c.GetFirst();
    EXPECT_EQ(data, 0);
}

TEST(List, can_get_last_elem)
{
    TList<int>c(10);
    for (int i = 0; i < 10; ++i) {
        c.InsLast(i);
    }
    int data = c.GetLast();
    EXPECT_EQ(data, 9);
}

TEST(List, can_get_list_with_multiplies_to_K)
{
    TList<int>c(10);
    for (int i = 0; i < 10; ++i) {
        c.InsLast(i);
    }
    TList<int>b = c.multiplesToK(2);
    TList<int>::iterator i = b.begin();
    while (i != b.end()) {
        EXPECT_EQ(*i % 2, 0);
        i++;
    }
}