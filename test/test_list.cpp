#include "list.h"
#include <gtest.h>

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> lst);
}

TEST(List, can_insert_node_front)
{
	List<int> lst;
	lst.push_front(1);
	lst.push_front(2);
	EXPECT_EQ(lst[0], 2);
	EXPECT_EQ(lst[1], 1);
}

TEST(List, can_insert_node_back)
{
	List<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	EXPECT_EQ(lst[0], 1);
	EXPECT_EQ(lst[1], 2);
}

TEST(List, can_insert_node_after_other_node)
{
	List<int> lst;
	lst.push_front(3);
	lst.push_front(1);
	lst.insert_after(0, 2);
	EXPECT_EQ(lst[1], 2);
	lst.insert_after(2, 4);
	EXPECT_EQ(lst[3], 4);
}

TEST(List, throws_when_insert_position_out_of_range)
{
	List<int> lst;
	lst.push_back(1);
	ASSERT_ANY_THROW(lst.insert_after(1, 2));
	ASSERT_ANY_THROW(lst.insert_after(-1, 2));
}

TEST(List, isempty_return_true_when_list_is_actually_empty)
{
	List<int> lst;
	EXPECT_EQ(true, lst.isEmpty());
	lst.push_front(1);
	EXPECT_EQ(false, lst.isEmpty());
}

TEST(List, can_erase_node_front)
{
	List<int> lst;
	lst.push_front(1);
	EXPECT_EQ(false, lst.isEmpty());
	lst.pop_front();
	EXPECT_EQ(true, lst.isEmpty());
}

TEST(List, throws_when_attempt_erase_node_from_empty_list)
{
	List<int> lst;
	ASSERT_ANY_THROW(lst.pop_front());
}

TEST(List, can_erase_node_after_other_node)
{
	List<int> lst;
	lst.push_front(3);
	lst.push_front(2);
	lst.push_front(1);
	EXPECT_EQ(lst[1], 2);
	lst.erase_after(0);
	EXPECT_EQ(lst[1], 3);
	lst.erase_after(0);
	EXPECT_EQ(1, lst.get_size());
	lst.push_back(2);
	EXPECT_EQ(2, lst[1]);
}

TEST(List, throws_when_erase_position_out_of_range)
{
	List<int> lst;
	lst.push_back(1);
	ASSERT_ANY_THROW(lst.erase_after(0));
	ASSERT_ANY_THROW(lst.erase_after(-1));
	ASSERT_ANY_THROW(lst.erase_after(1));
}

TEST(List, can_get_list_size)
{
	List<int> lst;
	EXPECT_EQ(0, lst.get_size());
	lst.push_front(1);
	lst.push_front(5);
	EXPECT_EQ(2, lst.get_size());
}

TEST(List, can_get_element)
{
	List<int> lst;
	lst.push_front(1);
	EXPECT_EQ(lst[0], 1);
}

TEST(List, throws_when_get_element_with_negative_index)
{
	List<int> lst;
	lst.push_front(1);
	ASSERT_ANY_THROW(lst.at(-1));
}

TEST(List, throws_when_get_element_with_too_large_index)
{
	List<int> lst;
	ASSERT_ANY_THROW(lst.at(0));
	lst.push_front(1);
	ASSERT_ANY_THROW(lst.at(1));
	ASSERT_ANY_THROW(lst.at(10));
}

TEST(List, can_compare_equal_lists_correctly)
{
	List<int> lst1;
	lst1.push_front(1);
	List<int> lst2;
	lst2.push_front(1);
	EXPECT_EQ(true, lst1 == lst2);
	EXPECT_EQ(false, lst1 != lst2);
}

TEST(List, can_create_copied_list)
{
	List<int> lst1;
	lst1.push_front(1);
	ASSERT_NO_THROW(List<int> lst2(lst1));
}

TEST(List, copied_list_is_equal_to_source_one)
{
	List<int> lst1;
	lst1.push_front(1);
	lst1.push_front(2);
	List<int> lst2(lst1);
	List<int> lst3;
	lst3.push_front(3);
	EXPECT_EQ(lst1, lst2);
	EXPECT_NE(lst1, lst3);
	EXPECT_NE(lst2, lst3);
}

TEST(List, copied_list_has_its_own_memory)
{
	List<int> lst1;
	lst1.push_front(3);
	lst1.push_front(2);
	lst1.push_front(1);
	List<int> lst2(lst1);
	lst2.erase_after(0);
	lst2.insert_after(0, 5);
	EXPECT_EQ(lst2[1], 5);
	EXPECT_NE(lst1[1], 5);
}

TEST(List, can_create_list_iterator)
{
	ASSERT_NO_THROW(List<int>::iterator iter);
}

TEST(List, can_set_beginning_of_iterator)
{
	List<int> lst;
	lst.push_front(1);
	List<int>::iterator iter;
	ASSERT_NO_THROW(iter = lst.begin());
	EXPECT_EQ(1, *iter);
}

TEST(List, can_compare_iterator_with_end)
{
	List<int> lst;
	lst.push_front(2);
	lst.push_front(1);
	List<int>::iterator iter = lst.begin();
	ASSERT_NO_THROW(iter != lst.end());
	ASSERT_NO_THROW(iter == lst.end());
}

TEST(List, can_dereference_iterator)
{
	List<int> lst;
	lst.push_front(1);
	List<int>::iterator iter = lst.begin();
	int value;
	ASSERT_NO_THROW(value = *iter);
	EXPECT_EQ(1, value);
}

TEST(List, can_moving_to_next_iteration)
{
	List<int> lst;
	lst.push_front(3);
	lst.push_front(2);
	lst.push_front(1);
	List<int>::iterator iter = lst.begin();
	ASSERT_NO_THROW(++iter);
	EXPECT_EQ(*iter, 2);
}
