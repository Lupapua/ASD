#include <gtest/gtest.h>
#include "../lib_stack/Stack.h"

TEST(StackTest, DefaultConstructor_CreatesEmptyStack) {
    Stack<int> s;
    ASSERT_TRUE(s.is_empty());
    ASSERT_TRUE(s.is_full());
    ASSERT_EQ(s.top(), -1); // top() возвращает индекс, для пустого стека -1
}

TEST(StackTest, SizeConstructor_CreatesEmptyStack) {
    Stack<int> s(3);
    ASSERT_TRUE(s.is_empty());
    ASSERT_FALSE(s.is_full());
    ASSERT_EQ(s.top(), -1);
}

TEST(StackTest, Push_UpdatesTopIndex) {
    Stack<int> s(3);

    s.push(10);
    ASSERT_EQ(s.top(), 0); // После первого push top = 0

    s.push(20);
    ASSERT_EQ(s.top(), 1); // После второго push top = 1

    s.push(30);
    ASSERT_EQ(s.top(), 2); // После третьего push top = 2
}

TEST(StackTest, Pop_UpdatesTopIndex) {
    Stack<int> s(3);
    s.push(10);
    s.push(20);
    s.push(30);

    ASSERT_EQ(s.top(), 2); // Начальный top
    s.pop();
    ASSERT_EQ(s.top(), 1); // После pop top уменьшился
    s.pop();
    ASSERT_EQ(s.top(), 0); // После второго pop top снова уменьшился
    s.pop();
    ASSERT_EQ(s.top(), -1); // После третьего pop стек пуст
}

TEST(StackTest, Push_ToFullStack_ThrowsException) {
    Stack<int> s(2);
    s.push(1);
    s.push(2);

    ASSERT_TRUE(s.is_full());
    ASSERT_EQ(s.top(), 1); // Максимальный индекс
    ASSERT_THROW(s.push(3), std::logic_error);
}

TEST(StackTest, Pop_FromEmptyStack_ThrowsException) {
    Stack<int> s(3);
    ASSERT_THROW(s.pop(), std::logic_error);
}

TEST(StackTest, IsFull_ReturnsCorrectState) {
    Stack<int> s(2);
    ASSERT_FALSE(s.is_full());

    s.push(1);
    ASSERT_FALSE(s.is_full());

    s.push(2);
    ASSERT_TRUE(s.is_full());

    s.pop();
    ASSERT_FALSE(s.is_full());
}

TEST(StackTest, IsEmpty_ReturnsCorrectState) {
    Stack<int> s(2);
    ASSERT_TRUE(s.is_empty());

    s.push(1);
    ASSERT_FALSE(s.is_empty());

    s.pop();
    ASSERT_TRUE(s.is_empty());
}

TEST(StackTest, Clear_ResetsTopIndex) {
    Stack<int> s(3);
    s.push(1);
    s.push(2);

    ASSERT_FALSE(s.is_empty());
    ASSERT_EQ(s.top(), 1);

    s.clear();

    ASSERT_TRUE(s.is_empty());
    ASSERT_EQ(s.top(), -1); // top сбрасывается в -1
}

TEST(StackTest, MultipleOperations_TopIndexBehavior) {
    Stack<int> s(4);

    // Серия операций push/pop
    s.push(1); // top = 0
    ASSERT_EQ(s.top(), 0);

    s.push(2); // top = 1
    ASSERT_EQ(s.top(), 1);

    s.pop();   // top = 0
    ASSERT_EQ(s.top(), 0);

    s.push(3); // top = 1
    ASSERT_EQ(s.top(), 1);

    s.push(4); // top = 2
    ASSERT_EQ(s.top(), 2);

    s.pop();   // top = 1
    ASSERT_EQ(s.top(), 1);

    s.push(5); // top = 2
    ASSERT_EQ(s.top(), 2);

    s.clear(); // top = -1
    ASSERT_EQ(s.top(), -1);
}

TEST(StackTest, BoundaryConditions_TopIndex) {
    Stack<int> s(1);

    // Пустой стек
    ASSERT_EQ(s.top(), -1);

    // Один элемент
    s.push(42);
    ASSERT_EQ(s.top(), 0);

    // Полный стек
    ASSERT_TRUE(s.is_full());

    // Снова пустой
    s.pop();
    ASSERT_EQ(s.top(), -1);
}

TEST(StackTest, StackLIFO_BehaviorWithTopIndex) {
    Stack<int> s(3);

    // Push трех элементов
    s.push(10); // top = 0
    s.push(20); // top = 1  
    s.push(30); // top = 2

    // Pop в порядке LIFO
    ASSERT_EQ(s.top(), 2);
    s.pop(); // top = 1

    ASSERT_EQ(s.top(), 1);
    s.pop(); // top = 0

    ASSERT_EQ(s.top(), 0);
    s.pop(); // top = -1

    ASSERT_TRUE(s.is_empty());
}

TEST(StackTest, CapacityOneStack_TopIndex) {
    Stack<int> s(1);

    ASSERT_EQ(s.top(), -1);
    ASSERT_TRUE(s.is_empty());

    s.push(100);
    ASSERT_EQ(s.top(), 0);
    ASSERT_TRUE(s.is_full());

    s.pop();
    ASSERT_EQ(s.top(), -1);
    ASSERT_TRUE(s.is_empty());
}