#include <gtest/gtest.h>
#include "../lib_stack/Stack.h"

TEST(StackTest, can_create_with_default_constructor) {
	Stack<int> p();
}

TEST(StackTest, can_create_wtih_size) {
	Stack<int> p(3);
	ASSERT_NO_THROW(p.push(3));
	ASSERT_NO_THROW(p.push(4));
	ASSERT_NO_THROW(p.push(5));
	ASSERT_ANY_THROW(p.push(6));
}