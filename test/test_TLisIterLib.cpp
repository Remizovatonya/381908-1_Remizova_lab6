#include "Stack.h"

#include "../gtest/gtest.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> S(3));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> S(-2));
}

TEST(TStack, can_create_copied_stack)
{
    TStack<int> S(5);
    ASSERT_NO_THROW(TStack<int> S1(S));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
    TStack<int> S(3), S1(S);
    EXPECT_EQ(S, S1);
}

TEST(TStack, can_assign_matrix_to_itself)
{
    TStack<int> S(5);
    ASSERT_NO_THROW(S = S);
}

TEST(TStack, can_assign_matrices_of_equal_size)
{
    TStack<int> S(5), S1(5);
    ASSERT_NO_THROW(S = S1);
}


TEST(TStack, can_assign_matrices_of_different_size)
{
    TStack<int> S(5), S1(3);
    ASSERT_NO_THROW(S = S1);
}

TEST(TStack, compare_equal_empty_stack_return_true)
{
    TStack<int> S(5), S1(5);
    ASSERT_EQ(S == S1, true);
}

TEST(TStack, compare_equal_stack_with_elements_return_true)
{
    TStack<int> S(2), S1(2);
    S.Push(7);
    S.Push(4);
    S1.Push(7);
    S1.Push(4);
    ASSERT_EQ(S == S1, true);
}

TEST(TStack, compare_stack_with_itself_return_true)
{
    TStack<int> S(5);
    ASSERT_EQ(S == S, true);
}

TEST(TStack, stack_with_different_size_are_not_equal)
{
    TStack<int> S(5), S1(3);
    ASSERT_EQ(S == S1, false);
}

TEST(TStack, stack_with_different_ind_are_not_equal)
{
    TStack<int> S(5), S1(5);
    S.Push(9);
    ASSERT_EQ(S == S1, false);
}

TEST(TStack, stack_with_different_elements_are_not_equal)
{
    TStack<int> S(5), S1(5);
    S.Push(9);
    S1.Push(8);
    ASSERT_EQ(S == S1, false);
}

TEST(TStack, can_push_element_in_not_full_stack)
{
    TStack<int> S(5);
    ASSERT_NO_THROW(S.Push(2));
}

TEST(TStack, cant_push_element_in_full_stack)
{
    TStack<int> S(3);
    S.Push(1);
    S.Push(2);
    S.Push(3);
    ASSERT_ANY_THROW(S.Push(4));
}

TEST(TStack, can_get_element_of_not_empty_stack)
{
    TStack<int> S(5);
    S.Push(9);
    ASSERT_NO_THROW(S.Get());
}

TEST(TStack, cant_get_element_of_empty_stack)
{
    TStack<int> S(3);
    ASSERT_ANY_THROW(S.Get());
}

TEST(TStack, get_return_element_pointed_by_ind)
{
    TStack<int> S(5);
    S.Push(7);
    S.Push(4);
    EXPECT_EQ(4, S.Get());
}

TEST(TStack, stack_with_null_ind_is_empty_and_return_true)
{
    TStack<int> S(5);
    ASSERT_EQ(S.IsEmpty(), true);
}

TEST(TStack, stack_with_not_null_ind_is_not_empty_and_return_false)
{
    TStack<int> S(5);
    S.Push(9);
    ASSERT_EQ(S.IsEmpty(), false);
}

TEST(TStack, stack_with_ind_equal_length_is_full_and_return_true)
{
    TStack<int> S(3);
    S.Push(9);
    S.Push(8);
    S.Push(7);
    ASSERT_EQ(S.IsFull(), true);
}

TEST(TStack, stack_with_ind_not_equal_length_is_not_full_and_return_false)
{
    TStack<int> S(5);
    S.Push(9);
    ASSERT_EQ(S.IsFull(), false);
}

TEST(TStack, can_get_length)
{
    TStack<int> S(5);
    EXPECT_EQ(5, S.GetLength());
}

TEST(TStack, can_get_ind)
{
    TStack<int> S(5);
    S.Push(7);
    EXPECT_EQ(1, S.GetInd());
}

