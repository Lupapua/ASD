#include <gtest/gtest.h>
#include "../lib_queue/Queue.h"

TEST(QueueTest, DefaultConstructor_CreatesEmptyQueue) {
    Queue<int> q;
    ASSERT_TRUE(q.is_empty());
    ASSERT_TRUE(q.is_full());
}

TEST(QueueTest, SizeConstructor_CreatesEmptyQueue) {
    Queue<int> q(3);
    ASSERT_TRUE(q.is_empty());
    ASSERT_FALSE(q.is_full());
    ASSERT_EQ(q.head(), 0); // head() возвращает индекс
}

TEST(QueueTest, Push_ToEmptyQueue_DoesNotChangeHeadIndex) {
    Queue<int> q(3);
    ASSERT_NO_THROW(q.push(10));
    ASSERT_EQ(q.head(), 0); // Индекс не меняется при push
}

TEST(QueueTest, Push_ToFullQueue_ThrowsException) {
    Queue<int> q(2);
    q.push(1);
    q.push(2);
    ASSERT_THROW(q.push(3), std::logic_error);
}

TEST(QueueTest, Pop_FromEmptyQueue_ThrowsException) {
    Queue<int> q(3);
    ASSERT_THROW(q.pop(), std::logic_error);
}

TEST(QueueTest, Pop_UpdatesHeadIndex) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);

    ASSERT_EQ(q.head(), 0); // Начальный индекс
    q.pop();
    ASSERT_EQ(q.head(), 1); // Индекс увеличился после pop
    q.pop();
    ASSERT_EQ(q.head(), 2); // Индекс снова увеличился
}

TEST(QueueTest, Pop_WrapsAroundCircularBuffer) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);

    // После трех pop должен вернуться к началу
    q.pop(); // head = 1
    q.pop(); // head = 2
    q.pop(); // head = 0 (3 % 3 = 0)

    ASSERT_EQ(q.head(), 0);
}

TEST(QueueTest, IsFull_ReturnsCorrectState) {
    Queue<int> q(2);
    ASSERT_FALSE(q.is_full());

    q.push(1);
    ASSERT_FALSE(q.is_full());

    q.push(2);
    ASSERT_TRUE(q.is_full());

    q.pop();
    ASSERT_FALSE(q.is_full());
}

TEST(QueueTest, IsEmpty_ReturnsCorrectState) {
    Queue<int> q(2);
    ASSERT_TRUE(q.is_empty());

    q.push(1);
    ASSERT_FALSE(q.is_empty());

    q.pop();
    ASSERT_TRUE(q.is_empty());
}

TEST(QueueTest, Clear_ResetsQueueStateAndHeadIndex) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.pop(); // head = 1

    ASSERT_FALSE(q.is_empty());
    ASSERT_EQ(q.head(), 1);

    q.clear();

    ASSERT_TRUE(q.is_empty());
    ASSERT_EQ(q.head(), 0); // head сбрасывается в 0
}

TEST(QueueTest, CircularBehavior_HeadIndexWrapsCorrectly) {
    Queue<int> q(3);

    // Заполняем очередь
    q.push(1); // head=0, count=1
    q.push(2); // head=0, count=2  
    q.push(3); // head=0, count=3

    // Удаляем элементы
    q.pop(); // head=1, count=2
    q.pop(); // head=2, count=1

    // Добавляем новые элементы
    q.push(4); // head=2, count=2
    q.push(5); // head=2, count=3

    // Проверяем индексы
    ASSERT_EQ(q.head(), 2);
    q.pop(); // head=0, count=2 (2+1 % 3 = 0)
    ASSERT_EQ(q.head(), 0);
}

TEST(QueueTest, CopyConstructor_CopiesHeadIndex) {
    Queue<int> original(3);
    original.push(1);
    original.push(2);
    original.pop(); // head=1

    Queue<int> copy(original);

    // Копия должна иметь тот же индекс head
    ASSERT_EQ(original.head(), copy.head());
    ASSERT_EQ(copy.head(), 1);
}

TEST(QueueTest, MultipleOperations_HeadIndexBehavior) {
    Queue<int> q(4);

    // Серия операций
    q.push(1); // head=0
    ASSERT_EQ(q.head(), 0);

    q.push(2); // head=0
    ASSERT_EQ(q.head(), 0);

    q.pop();   // head=1
    ASSERT_EQ(q.head(), 1);

    q.push(3); // head=1  
    ASSERT_EQ(q.head(), 1);

    q.pop();   // head=2
    ASSERT_EQ(q.head(), 2);

    q.push(4); // head=2
    ASSERT_EQ(q.head(), 2);

    q.push(5); // head=2
    ASSERT_EQ(q.head(), 2);
}