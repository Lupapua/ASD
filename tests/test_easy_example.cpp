#include <gtest/gtest.h>
#include "../lib_list/DoubleList.h"

TEST(TestDoubleListLib, CanCreateWithDefaultConstructor) {
    DoubleList<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin(), nullptr);
    EXPECT_EQ(list.size(), 0);
}

TEST(TestDoubleListLib, PushAndPop) {
    DoubleList<int> list;
    list.push_front(4);
    list.push_back(5);
    list.push_back(6);
    list.push_front(3);

    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 6);

    DoubleList<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(5);
    list2.push_back(6);

    list2.pop_back();
    EXPECT_EQ(list2.size(), 5);
    EXPECT_EQ(list2.back(), 5);

    list2.pop_front();
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2.front(), 2);
}

TEST(TestDoubleListLib, CopyConstructor) {
    DoubleList<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    DoubleList<int> copy(original);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);
}

TEST(TestDoubleListLib, InsertByPosition) {
    DoubleList<int> list1;
    list1.push_back(1);
    list1.push_back(3);

    list1.insert(2, 1);
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1.front(), 1);
    EXPECT_EQ(list1.find(2)->_value, 2);
    EXPECT_EQ(list1.back(), 3);

    DoubleList<int> list2;
    list2.push_back(2);
    list2.insert(1, 0);
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);

    DoubleList<int> list3;
    list3.push_back(5);
    list3.insert(6, 1);
    EXPECT_EQ(list3.size(), 2);
    EXPECT_EQ(list3.front(), 5);
    EXPECT_EQ(list3.back(), 6);
}

TEST(TestDoubleListLib, EraseByPosition) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(TestDoubleListLib, EraseByNode) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(list.begin()->_next);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(TestDoubleListLib, Find) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(8);
    list.push_back(7);

    EXPECT_EQ(list.find(8)->_value, 8);
    EXPECT_EQ(list.find(99), nullptr);
}

TEST(TestDoubleListLib, Clear) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

    DoubleList<int> list2;
    list2.clear();
    EXPECT_TRUE(list2.is_empty());
}

TEST(TestDoubleListIterator, ReadForward) {
    DoubleList<int> list;
    list.push_back(100);
    list.push_back(200);
    list.push_back(300);

    DoubleList<int>::Iterator it = list.begin_iter();
    EXPECT_EQ(*it, 100);

    it++;
    EXPECT_EQ(*it, 200);

    it++;
    EXPECT_EQ(*it, 300);

    it++;
    EXPECT_EQ(it, list.end_iter());
}

TEST(TestDoubleListIterator, ReadBackward) {
    DoubleList<int> list;
    list.push_back(100);
    list.push_back(200);
    list.push_back(300);

    DoubleList<int>::Iterator it = list.rbegin_iter();
    EXPECT_EQ(*it, 300);

    --it;
    EXPECT_EQ(*it, 200);

    --it;
    EXPECT_EQ(*it, 100);

    --it;
    EXPECT_EQ(it, list.rend_iter());
}

TEST(TestDoubleListIterator, WriteForward) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int tmp = 10;
    for (DoubleList<int>::Iterator it = list.begin_iter(); it != list.end_iter(); it++) {
        *it = tmp;
        tmp += 5;
    }

    DoubleList<int>::Iterator it = list.begin_iter();
    EXPECT_EQ(*it, 10);

    it++;
    EXPECT_EQ(*it, 15);

    it++;
    EXPECT_EQ(*it, 20);
}

TEST(TestDoubleListIterator, WriteBackward) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    DoubleList<int>::Iterator it = list.rbegin_iter();
    int tmp = 30;
    while (true) {
        *it = tmp;
        if (it == list.begin_iter()) break;
        tmp -= 10;
        --it;
    }

    it = list.begin_iter();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}


TEST(TestDoubleListIterator, EmptyForward) {
    DoubleList<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin_iter(), list.end_iter());

    DoubleList<int>::Iterator it1 = list.begin_iter();
    DoubleList<int>::Iterator it2 = it1++;
    EXPECT_EQ(it1, list.end_iter());
    EXPECT_EQ(it2, list.end_iter());

    DoubleList<int>::Iterator it3 = list.begin_iter();
    ++it3;
    EXPECT_EQ(it3, list.end_iter());
}

TEST(TestDoubleListIterator, EmptyBackward) {
    DoubleList<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.rbegin_iter(), list.rend_iter());

    DoubleList<int>::Iterator it1 = list.rbegin_iter();
    DoubleList<int>::Iterator it2 = it1--;
    EXPECT_EQ(it1, list.rend_iter());
    EXPECT_EQ(it2, list.rend_iter());

    DoubleList<int>::Iterator it3 = list.rbegin_iter();
    --it3;
    EXPECT_EQ(it3, list.rend_iter());
}