#include <gtest/gtest.h>
#include <sstream>
#include "../lib_table/TableList.h"
#include "../lib_table/ITable.h"

// ==================== UnsortedTableOnList Tests ====================

class UnsortedTableOnListTest : public ::testing::Test {
protected:
    UnsortedTableOnList<int, std::string> table;
};

// Конструктор и базовые проверки
TEST_F(UnsortedTableOnListTest, DefaultConstructorCreatesEmptyTable) {
    EXPECT_TRUE(table.is_empty());
}

// Вставка одного элемента
TEST_F(UnsortedTableOnListTest, InsertSingleElement) {
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(1));
}

// Вставка нескольких элементов
TEST_F(UnsortedTableOnListTest, InsertMultipleElements) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

// Вставка дубликата ключа вызывает исключение
TEST_F(UnsortedTableOnListTest, InsertDuplicateKeyThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.insert(5, "FIVE"), std::logic_error);
}

// Поиск существующего элемента
TEST_F(UnsortedTableOnListTest, FindExistingElement) {
    table.insert(10, "ten");
    EXPECT_EQ(table.find(10), "ten");
}

// Поиск первого вставленного элемента
TEST_F(UnsortedTableOnListTest, FindFirstElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_EQ(table.find(1), "one");
}

// Поиск последнего вставленного элемента
TEST_F(UnsortedTableOnListTest, FindLastElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_EQ(table.find(3), "three");
}

// Поиск несуществующего элемента вызывает исключение
TEST_F(UnsortedTableOnListTest, FindNonexistentElementThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.find(99), std::logic_error);
}

// Поиск в пустой таблице вызывает исключение
TEST_F(UnsortedTableOnListTest, FindInEmptyTableThrows) {
    EXPECT_THROW(table.find(1), std::logic_error);
}

// Проверка существования ключа
TEST_F(UnsortedTableOnListTest, ConsistReturnsTrue) {
    table.insert(5, "five");
    EXPECT_TRUE(table.consist(5));
}

// Проверка несуществующего ключа
TEST_F(UnsortedTableOnListTest, ConsistReturnsFalse) {
    table.insert(5, "five");
    EXPECT_FALSE(table.consist(99));
}

// Проверка несуществующего ключа в пустой таблице
TEST_F(UnsortedTableOnListTest, ConsistInEmptyTableReturnsFalse) {
    EXPECT_FALSE(table.consist(1));
}

// Удаление первого элемента
TEST_F(UnsortedTableOnListTest, EraseFirstElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.erase(1);
    EXPECT_FALSE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
}

// Удаление последнего элемента
TEST_F(UnsortedTableOnListTest, EraseLastElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(3);
    EXPECT_FALSE(table.consist(3));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
}

// Удаление среднего элемента
TEST_F(UnsortedTableOnListTest, EraseMiddleElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

// Удаление единственного элемента
TEST_F(UnsortedTableOnListTest, EraseSingleElement) {
    table.insert(5, "five");
    table.erase(5);
    EXPECT_TRUE(table.is_empty());
}

// Удаление несуществующего ключа вызывает исключение
TEST_F(UnsortedTableOnListTest, EraseNonexistentKeyThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.erase(99), std::logic_error);
}

// Удаление из пустой таблицы вызывает исключение
TEST_F(UnsortedTableOnListTest, EraseFromEmptyTableThrows) {
    EXPECT_THROW(table.erase(1), std::logic_error);
}

// Replace: вставка нового ключа
TEST_F(UnsortedTableOnListTest, ReplaceInsertNewKey) {
    table.replace(1, "one");
    EXPECT_TRUE(table.consist(1));
    EXPECT_EQ(table.find(1), "one");
}

// Replace: обновление существующего значения
TEST_F(UnsortedTableOnListTest, ReplaceUpdateValue) {
    table.insert(5, "five");
    table.replace(5, "FIVE");
    EXPECT_EQ(table.find(5), "FIVE");
}

// Replace: несколько операций
TEST_F(UnsortedTableOnListTest, ReplaceMultipleOperations) {
    table.replace(1, "one");
    table.replace(2, "two");
    table.replace(1, "ONE");
    EXPECT_EQ(table.find(1), "ONE");
    EXPECT_EQ(table.find(2), "two");
}

// Print: проверка формата вывода
TEST_F(UnsortedTableOnListTest, PrintFormatIsCorrect) {
    table.insert(5, "five");
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("|5|") != std::string::npos);
    EXPECT_TRUE(output.find("|five|") != std::string::npos);
}

// Print: пустая таблица
TEST_F(UnsortedTableOnListTest, PrintEmptyTable) {
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    EXPECT_EQ(output, "");
}

// Большое количество элементов
TEST_F(UnsortedTableOnListTest, LargeNumberOfElements) {
    for (int i = 0; i < 100; ++i) {
        table.insert(i, "value_" + std::to_string(i));
    }
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(50));
    EXPECT_EQ(table.find(50), "value_50");
}

// Типы: string ключи, int значения
TEST(UnsortedTableOnListTypes, StringKeyIntValue) {
    UnsortedTableOnList<std::string, int> table;
    table.insert("apple", 1);
    table.insert("banana", 2);
    EXPECT_EQ(table.find("apple"), 1);
    EXPECT_EQ(table.find("banana"), 2);
}

// Типы: double ключи, string значения
TEST(UnsortedTableOnListTypes, DoubleKeyStringValue) {
    UnsortedTableOnList<double, std::string> table;
    table.insert(3.14, "pi");
    table.insert(2.71, "e");
    EXPECT_EQ(table.find(3.14), "pi");
}

// ==================== UnsortedTableOnVec Tests ====================

class UnsortedTableOnVecTest : public ::testing::Test {
protected:
    UnsortedTableOnVec<int, std::string> table;
};

TEST_F(UnsortedTableOnVecTest, DefaultConstructorCreatesEmptyTable) {
    EXPECT_TRUE(table.is_empty());
}

TEST_F(UnsortedTableOnVecTest, InsertSingleElement) {
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(1));
}

TEST_F(UnsortedTableOnVecTest, InsertMultipleElements) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

// Вставка дубликатов: таблица на векторе позволяет дубликаты
TEST_F(UnsortedTableOnVecTest, InsertDuplicateKeysAllowed) {
    table.insert(5, "five");
    table.insert(5, "FIVE");
    EXPECT_TRUE(table.consist(5));
    // Найдёт первое вхождение
    EXPECT_EQ(table.find(5), "five");
}

TEST_F(UnsortedTableOnVecTest, FindExistingElement) {
    table.insert(10, "ten");
    EXPECT_EQ(table.find(10), "ten");
}

TEST_F(UnsortedTableOnVecTest, FindFirstElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_EQ(table.find(1), "one");
}

TEST_F(UnsortedTableOnVecTest, FindLastElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_EQ(table.find(3), "three");
}

TEST_F(UnsortedTableOnVecTest, FindNonexistentElementThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.find(99), std::logic_error);
}

TEST_F(UnsortedTableOnVecTest, FindInEmptyTableThrows) {
    EXPECT_THROW(table.find(1), std::logic_error);
}

TEST_F(UnsortedTableOnVecTest, ConsistReturnsTrue) {
    table.insert(5, "five");
    EXPECT_TRUE(table.consist(5));
}

TEST_F(UnsortedTableOnVecTest, ConsistReturnsFalse) {
    table.insert(5, "five");
    EXPECT_FALSE(table.consist(99));
}

TEST_F(UnsortedTableOnVecTest, ConsistInEmptyTableReturnsFalse) {
    EXPECT_FALSE(table.consist(1));
}

TEST_F(UnsortedTableOnVecTest, EraseFirstElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.erase(1);
    EXPECT_FALSE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
}

TEST_F(UnsortedTableOnVecTest, EraseLastElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(3);
    EXPECT_FALSE(table.consist(3));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
}

TEST_F(UnsortedTableOnVecTest, EraseMiddleElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST_F(UnsortedTableOnVecTest, EraseSingleElement) {
    table.insert(5, "five");
    table.erase(5);
    EXPECT_TRUE(table.is_empty());
}

TEST_F(UnsortedTableOnVecTest, EraseNonexistentKeyThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.erase(99), std::logic_error);
}

TEST_F(UnsortedTableOnVecTest, EraseFromEmptyTableThrows) {
    EXPECT_THROW(table.erase(1), std::logic_error);
}

TEST_F(UnsortedTableOnVecTest, PrintFormatIsCorrect) {
    table.insert(5, "five");
    table.insert(3, "three");
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("5") != std::string::npos);
    EXPECT_TRUE(output.find("three") != std::string::npos);
}

TEST_F(UnsortedTableOnVecTest, PrintEmptyTable) {
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("{}") != std::string::npos || output == "{ }");
}

TEST_F(UnsortedTableOnVecTest, LargeNumberOfElements) {
    for (int i = 0; i < 100; ++i) {
        table.insert(i, "value_" + std::to_string(i));
    }
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(50));
    EXPECT_EQ(table.find(50), "value_50");
}

TEST(UnsortedTableOnVecTypes, StringKeyIntValue) {
    UnsortedTableOnVec<std::string, int> table;
    table.insert("apple", 1);
    table.insert("banana", 2);
    EXPECT_EQ(table.find("apple"), 1);
    EXPECT_EQ(table.find("banana"), 2);
}

TEST(UnsortedTableOnVecTypes, DoubleKeyStringValue) {
    UnsortedTableOnVec<double, std::string> table;
    table.insert(3.14, "pi");
    table.insert(2.71, "e");
    EXPECT_EQ(table.find(3.14), "pi");
}

// ==================== SortedTableOnVec Tests ====================

class SortedTableOnVecTest : public ::testing::Test {
protected:
    SortedTableOnVec<int, std::string> table;
};

TEST_F(SortedTableOnVecTest, DefaultConstructorCreatesEmptyTable) {
    EXPECT_TRUE(table.is_empty());
}

TEST_F(SortedTableOnVecTest, InsertSingleElement) {
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(1));
}

// Вставка в возрастающем порядке
TEST_F(SortedTableOnVecTest, InsertAscendingOrder) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

// Вставка в убывающем порядке (тест сортировки)
TEST_F(SortedTableOnVecTest, InsertDescendingOrder) {
    table.insert(3, "three");
    table.insert(2, "two");
    table.insert(1, "one");
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

// Вставка в случайном порядке
TEST_F(SortedTableOnVecTest, InsertRandomOrder) {
    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");
    table.insert(9, "nine");
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(8));
    EXPECT_TRUE(table.consist(9));
}

// Вставка дубликата ключа обновляет значение
TEST_F(SortedTableOnVecTest, InsertDuplicateKeyUpdatesValue) {
    table.insert(5, "five");
    table.insert(5, "FIVE");
    EXPECT_EQ(table.find(5), "FIVE");
}

TEST_F(SortedTableOnVecTest, FindExistingElement) {
    table.insert(10, "ten");
    EXPECT_EQ(table.find(10), "ten");
}

// Поиск элемента в начале
TEST_F(SortedTableOnVecTest, FindFirstElement) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    EXPECT_EQ(table.find(3), "three");
}

// Поиск элемента в конце
TEST_F(SortedTableOnVecTest, FindLastElement) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    EXPECT_EQ(table.find(7), "seven");
}

// Поиск элемента в середине
TEST_F(SortedTableOnVecTest, FindMiddleElement) {
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    EXPECT_EQ(table.find(5), "five");
}

TEST_F(SortedTableOnVecTest, FindNonexistentElementThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.find(99), std::logic_error);
}

TEST_F(SortedTableOnVecTest, FindInEmptyTableThrows) {
    EXPECT_THROW(table.find(1), std::logic_error);
}

// Поиск с отрицательными ключами
TEST_F(SortedTableOnVecTest, FindWithNegativeKeys) {
    table.insert(-5, "minus five");
    table.insert(0, "zero");
    table.insert(5, "five");
    EXPECT_EQ(table.find(-5), "minus five");
    EXPECT_EQ(table.find(0), "zero");
    EXPECT_EQ(table.find(5), "five");
}

TEST_F(SortedTableOnVecTest, ConsistReturnsTrue) {
    table.insert(5, "five");
    EXPECT_TRUE(table.consist(5));
}

TEST_F(SortedTableOnVecTest, ConsistReturnsFalse) {
    table.insert(5, "five");
    EXPECT_FALSE(table.consist(99));
}

TEST_F(SortedTableOnVecTest, ConsistInEmptyTableReturnsFalse) {
    EXPECT_FALSE(table.consist(1));
}

// Удаление единственного элемента
TEST_F(SortedTableOnVecTest, EraseSingleElement) {
    table.insert(5, "five");
    table.erase(5);
    EXPECT_TRUE(table.is_empty());
}

// Удаление первого элемента
TEST_F(SortedTableOnVecTest, EraseFirstElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(1);
    EXPECT_FALSE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

// Удаление последнего элемента
TEST_F(SortedTableOnVecTest, EraseLastElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(3);
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_FALSE(table.consist(3));
}

// Удаление среднего элемента
TEST_F(SortedTableOnVecTest, EraseMiddleElement) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST_F(SortedTableOnVecTest, EraseNonexistentKeyThrows) {
    table.insert(5, "five");
    EXPECT_THROW(table.erase(99), std::logic_error);
}

TEST_F(SortedTableOnVecTest, EraseFromEmptyTableThrows) {
    EXPECT_THROW(table.erase(1), std::logic_error);
}

// Удаление всех элементов по одному
TEST_F(SortedTableOnVecTest, EraseAllElementsOneByOne) {
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(1);
    table.erase(2);
    table.erase(3);
    EXPECT_TRUE(table.is_empty());
}

TEST_F(SortedTableOnVecTest, PrintFormatIsCorrect) {
    table.insert(5, "five");
    table.insert(3, "three");
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("3") != std::string::npos);
    EXPECT_TRUE(output.find("5") != std::string::npos);
}

TEST_F(SortedTableOnVecTest, PrintEmptyTable) {
    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("{}") != std::string::npos || output == "{ }");
}

// Проверка сортировки после вставок
TEST_F(SortedTableOnVecTest, ElementsAreSorted) {
    table.insert(5, "five");
    table.insert(2, "two");
    table.insert(8, "eight");
    table.insert(1, "one");
    
    // Элементы должны быть найдены корректно (что гарантирует правильную сортировку)
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(8), "eight");
}

TEST_F(SortedTableOnVecTest, LargeNumberOfElements) {
    for (int i = 0; i < 100; ++i) {
        table.insert(i, "value_" + std::to_string(i));
    }
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(50));
    EXPECT_EQ(table.find(50), "value_50");
}

// Типы: string ключи, int значения
TEST(SortedTableOnVecTypes, StringKeyIntValue) {
    SortedTableOnVec<std::string, int> table;
    table.insert("apple", 1);
    table.insert("banana", 2);
    table.insert("cherry", 3);
    EXPECT_EQ(table.find("apple"), 1);
    EXPECT_EQ(table.find("banana"), 2);
    EXPECT_EQ(table.find("cherry"), 3);
}

// Типы: double ключи, string значения
TEST(SortedTableOnVecTypes, DoubleKeyStringValue) {
    SortedTableOnVec<double, std::string> table;
    table.insert(3.14, "pi");
    table.insert(2.71, "e");
    table.insert(1.41, "sqrt2");
    EXPECT_EQ(table.find(1.41), "sqrt2");
    EXPECT_EQ(table.find(2.71), "e");
    EXPECT_EQ(table.find(3.14), "pi");
}

// Граничный случай: очень близкие double значения
TEST(SortedTableOnVecTypes, VeryCloseDoubleValues) {
    SortedTableOnVec<double, int> table;
    table.insert(1.0, 1);
    table.insert(1.0000001, 2);
    table.insert(0.9999999, 3);
    EXPECT_EQ(table.find(1.0), 1);
}