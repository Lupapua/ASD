#include <gtest/gtest.h>
#include <sstream>
#include "../lib_table/BSTTable.h"

// ==================== BSTreeTable Tests ====================

class BSTreeTableTest : public ::testing::Test {
protected:
    BSTreeTable<int, std::string> table;
};

// ==================== Конструктор и базовые состояния ====================

TEST_F(BSTreeTableTest, DefaultConstructorCreatesEmptyTable) {
    EXPECT_TRUE(table.is_empty());
}

// ==================== Вставка (insert) ====================

TEST_F(BSTreeTableTest, InsertSingleElement) {
    table.insert(5, "five");
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(5));
}

TEST_F(BSTreeTableTest, InsertMultipleElements) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(7));
}

TEST_F(BSTreeTableTest, InsertAscendingOrder) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST_F(BSTreeTableTest, InsertDescendingOrder) {
    table.insert(3, "three");
    table.insert(2, "two");
    table.insert(1, "one");
    EXPECT_EQ(table.find(3), "three");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(1), "one");
}

TEST_F(BSTreeTableTest, InsertRandomOrder) {
    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");
    table.insert(9, "nine");
    table.insert(3, "three");
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(9), "nine");
}

TEST_F(BSTreeTableTest, InsertDuplicateKeyUpdatesValue) {
    table.insert(5, "five");
    table.insert(5, "FIVE");
    EXPECT_EQ(table.find(5), "FIVE");
}

TEST_F(BSTreeTableTest, InsertMultipleDuplicateKeyUpdates) {
    table.insert(10, "ten");
    table.insert(10, "TEN");
    table.insert(10, "TEN_CAPS");
    EXPECT_EQ(table.find(10), "TEN_CAPS");
    EXPECT_TRUE(table.consist(10));
}

TEST_F(BSTreeTableTest, InsertEmptyThenDuplicate) {
    table.insert(1, "value1");
    EXPECT_EQ(table.find(1), "value1");
    table.insert(1, "value2");
    EXPECT_EQ(table.find(1), "value2");
    EXPECT_TRUE(table.is_empty() == false);
}

// ==================== Поиск (find) ====================

TEST_F(BSTreeTableTest, FindExistingElement) {
    table.insert(10, "ten");
    EXPECT_EQ(table.find(10), "ten");
}

TEST_F(BSTreeTableTest, FindFirstElement) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    EXPECT_EQ(table.find(3), "three");
}

TEST_F(BSTreeTableTest, FindLastElement) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    EXPECT_EQ(table.find(7), "seven");
}

TEST_F(BSTreeTableTest, FindMiddleElement) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    EXPECT_EQ(table.find(5), "five");
}

TEST_F(BSTreeTableTest, FindNonexistentElementThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.find(99), std::logic_error);
}

TEST_F(BSTreeTableTest, FindInEmptyTableThrows) {
    EXPECT_THROW(table.find(1), std::logic_error);
}

TEST_F(BSTreeTableTest, FindAfterEraseAll) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.erase(1);
    table.erase(2);
    EXPECT_THROW(table.find(1), std::logic_error);
}

TEST_F(BSTreeTableTest, FindWithNegativeKeys) {
    table.insert(-5, "minus five");
    table.insert(0, "zero");
    table.insert(5, "five");
    EXPECT_EQ(table.find(-5), "minus five");
    EXPECT_EQ(table.find(0), "zero");
    EXPECT_EQ(table.find(5), "five");
}

// ==================== Проверка наличия (consist) ====================

TEST_F(BSTreeTableTest, ConsistReturnsTrue) {
    table.insert(5, "five");
    EXPECT_TRUE(table.consist(5));
}

TEST_F(BSTreeTableTest, ConsistReturnsFalse) {
    table.insert(5, "five");
    EXPECT_FALSE(table.consist(99));
}

TEST_F(BSTreeTableTest, ConsistInEmptyTableReturnsFalse) {
    EXPECT_FALSE(table.consist(1));
}

TEST_F(BSTreeTableTest, ConsistAfterErase) {
    table.insert(5, "five");
    EXPECT_TRUE(table.consist(5));
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
}

TEST_F(BSTreeTableTest, ConsistWithNegativeKeys) {
    table.insert(-10, "minus ten");
    EXPECT_TRUE(table.consist(-10));
    EXPECT_FALSE(table.consist(-11));
}

// ==================== Удаление (erase) ====================

TEST_F(BSTreeTableTest, EraseSingleElement) {
    table.insert(5, "five");
    table.erase(5);
    EXPECT_TRUE(table.is_empty());
}

TEST_F(BSTreeTableTest, EraseRootSingleNode) {
    table.insert(100, "one_hundred");
    table.erase(100);
    EXPECT_TRUE(table.is_empty());
    EXPECT_THROW(table.find(100), std::logic_error);
}

TEST_F(BSTreeTableTest, EraseFirstElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(1);
    EXPECT_FALSE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST_F(BSTreeTableTest, EraseLastElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(3);
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_FALSE(table.consist(3));
}

TEST_F(BSTreeTableTest, EraseMiddleElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST_F(BSTreeTableTest, EraseLeafNode) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.erase(3);
    EXPECT_FALSE(table.consist(3));
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(7));
}

TEST_F(BSTreeTableTest, EraseNodeWithOneChild) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(6, "six");
    table.erase(7);
    EXPECT_FALSE(table.consist(7));
    EXPECT_TRUE(table.consist(6));
    EXPECT_EQ(table.find(6), "six");
}

TEST_F(BSTreeTableTest, EraseNodeWithTwoChildren) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(2, "two");
    table.insert(4, "four");
    table.insert(6, "six");
    table.insert(8, "eight");
    
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(4));
    EXPECT_TRUE(table.consist(6));
    EXPECT_TRUE(table.consist(7));
    EXPECT_TRUE(table.consist(8));
}

TEST_F(BSTreeTableTest, EraseNonexistentKeyThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.erase(99), std::logic_error);
}

TEST_F(BSTreeTableTest, EraseFromEmptyTableThrows) {
    EXPECT_THROW(table.erase(1), std::logic_error);
}

TEST_F(BSTreeTableTest, EraseAllElementsOneByOne) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    
    table.erase(1);
    EXPECT_FALSE(table.is_empty());
    
    table.erase(2);
    EXPECT_FALSE(table.is_empty());
    
    table.erase(3);
    EXPECT_TRUE(table.is_empty());
}

TEST_F(BSTreeTableTest, EraseAfterDuplicateInsert) {
    table.insert(5, "five");
    table.insert(5, "FIVE");
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    EXPECT_TRUE(table.is_empty());
}

// ==================== Печать (print) ====================

TEST_F(BSTreeTableTest, PrintFormatIsCorrect) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    
    EXPECT_TRUE(output.find("3") != std::string::npos);
    EXPECT_TRUE(output.find("5") != std::string::npos);
    EXPECT_TRUE(output.find("7") != std::string::npos);
}

TEST_F(BSTreeTableTest, PrintEmptyTable) {
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("{}") != std::string::npos || output == "{ }");
}

TEST_F(BSTreeTableTest, PrintAfterOperations) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.erase(3);
    
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    
    EXPECT_TRUE(output.find("5") != std::string::npos);
    EXPECT_TRUE(output.find("7") != std::string::npos);
    EXPECT_FALSE(output.find("3") != std::string::npos);
}

// ==================== Комбинированные операции ====================

TEST_F(BSTreeTableTest, LargeNumberOfElements) {
    for (int i = 0; i < 100; ++i) {
        table.insert(i, "value_" + std::to_string(i));
    }
    
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(0));
    EXPECT_TRUE(table.consist(50));
    EXPECT_TRUE(table.consist(99));
    EXPECT_EQ(table.find(50), "value_50");
}

TEST_F(BSTreeTableTest, InsertEraseInsertCycle) {
    table.insert(5, "five");
    EXPECT_TRUE(table.consist(5));
    
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    
    table.insert(5, "FIVE");
    EXPECT_TRUE(table.consist(5));
    EXPECT_EQ(table.find(5), "FIVE");
}

TEST_F(BSTreeTableTest, InterleavedOperations) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    
    EXPECT_EQ(table.find(5), "five");
    table.insert(5, "FIVE");
    EXPECT_EQ(table.find(5), "FIVE");
    
    table.erase(3);
    EXPECT_FALSE(table.consist(3));
    
    table.insert(1, "one");
    EXPECT_TRUE(table.consist(1));
}

TEST_F(BSTreeTableTest, EraseAndReinsertDifferent) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    
    table.erase(2);
    table.insert(4, "four");
    
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(4));
}

// ==================== Типы данных ====================

TEST(BSTreeTableTypes, StringKeyIntValue) {
    BSTreeTable<std::string, int> table;
    table.insert("apple", 1);
    table.insert("banana", 2);
    table.insert("cherry", 3);
    
    EXPECT_EQ(table.find("apple"), 1);
    EXPECT_EQ(table.find("banana"), 2);
    EXPECT_EQ(table.find("cherry"), 3);
}

TEST(BSTreeTableTypes, DoubleKeyStringValue) {
    BSTreeTable<double, std::string> table;
    table.insert(3.14, "pi");
    table.insert(2.71, "e");
    table.insert(1.41, "sqrt2");
    
    EXPECT_EQ(table.find(3.14), "pi");
    EXPECT_EQ(table.find(2.71), "e");
    EXPECT_EQ(table.find(1.41), "sqrt2");
}

TEST(BSTreeTableTypes, NegativeKeyValues) {
    BSTreeTable<int, std::string> table;
    table.insert(-5, "minus five");
    table.insert(-10, "minus ten");
    table.insert(0, "zero");
    table.insert(5, "five");
    
    EXPECT_EQ(table.find(-10), "minus ten");
    EXPECT_EQ(table.find(-5), "minus five");
    EXPECT_EQ(table.find(0), "zero");
    EXPECT_EQ(table.find(5), "five");
}

TEST(BSTreeTableTypes, ExtremeKeyValues) {
    BSTreeTable<long long, std::string> table;
    table.insert(LLONG_MIN, "min");
    table.insert(0, "zero");
    table.insert(LLONG_MAX, "max");
    
    EXPECT_EQ(table.find(LLONG_MIN), "min");
    EXPECT_EQ(table.find(0), "zero");
    EXPECT_EQ(table.find(LLONG_MAX), "max");
}

// ==================== Граничные случаи ёмкости ====================

TEST_F(BSTreeTableTest, SingleElementOperations) {
    table.insert(42, "answer");
    EXPECT_EQ(table.find(42), "answer");
    EXPECT_TRUE(table.consist(42));
    EXPECT_FALSE(table.consist(41));
    EXPECT_FALSE(table.is_empty());
}

TEST_F(BSTreeTableTest, SequentialEraseInInsertOrder) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    
    table.erase(1);
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    
    table.erase(2);
    EXPECT_TRUE(table.consist(3));
    
    table.erase(3);
    EXPECT_TRUE(table.is_empty());
}

TEST_F(BSTreeTableTest, SequentialEraseInReverseOrder) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    
    table.erase(3);
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    
    table.erase(2);
    EXPECT_TRUE(table.consist(1));
    
    table.erase(1);
    EXPECT_TRUE(table.is_empty());
}