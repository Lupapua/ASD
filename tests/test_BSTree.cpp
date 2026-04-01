#include <gtest/gtest.h>
#include "../lib_bstree/BSTree.h"

// ==================== BSTree Basic Tests ====================

class BSTreeTest : public ::testing::Test {
protected:
    BSTree<int, std::string> tree;
};

// Конструктор создаёт пустое дерево
TEST_F(BSTreeTest, DefaultConstructorCreatesEmptyTree) {
    EXPECT_TRUE(tree.is_empty());
}

// Вставка одного элемента
TEST_F(BSTreeTest, InsertSingleElement) {
    tree.insert(5, "five");
    EXPECT_FALSE(tree.is_empty());
}

// Вставка нескольких элементов в порядке возрастания
TEST_F(BSTreeTest, InsertAscendingOrder) {
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");
    tree.insert(5, "five");
    EXPECT_FALSE(tree.is_empty());
}

// Вставка нескольких элементов в порядке убывания
TEST_F(BSTreeTest, InsertDescendingOrder) {
    tree.insert(5, "five");
    tree.insert(4, "four");
    tree.insert(3, "three");
    tree.insert(2, "two");
    tree.insert(1, "one");
    EXPECT_FALSE(tree.is_empty());
}

// Вставка в случайном порядке (сбалансированное дерево)
TEST_F(BSTreeTest, InsertRandomOrder) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");
    tree.insert(6, "six");
    tree.insert(8, "eight");
    EXPECT_FALSE(tree.is_empty());
}

// Вставка дубликата ключа вызывает исключение
TEST_F(BSTreeTest, InsertDuplicateKeyThrows) {
    tree.insert(5, "five");
    EXPECT_THROW(tree.insert(5, "FIVE"), std::logic_error);
}

// ==================== BSTree Find Tests ====================

// Поиск существующего элемента
TEST_F(BSTreeTest, FindExistingElement) {
    tree.insert(5, "five");
    EXPECT_EQ(tree.find(5), "five");
}

// Поиск корня (первого вставленного элемента)
TEST_F(BSTreeTest, FindRoot) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    EXPECT_EQ(tree.find(5), "five");
}

// Поиск левого потомка
TEST_F(BSTreeTest, FindLeftChild) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    EXPECT_EQ(tree.find(3), "three");
}

// Поиск правого потомка
TEST_F(BSTreeTest, FindRightChild) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    EXPECT_EQ(tree.find(7), "seven");
}

// Поиск элемента в левом поддереве
TEST_F(BSTreeTest, FindInLeftSubtree) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(1, "one");
    EXPECT_EQ(tree.find(1), "one");
}

// Поиск элемента в правом поддереве
TEST_F(BSTreeTest, FindInRightSubtree) {
    tree.insert(5, "five");
    tree.insert(7, "seven");
    tree.insert(9, "nine");
    EXPECT_EQ(tree.find(9), "nine");
}

// Поиск несуществующего ключа вызывает исключение
TEST_F(BSTreeTest, FindNonexistentKeyThrows) {
    tree.insert(5, "five");
    EXPECT_THROW(tree.find(99), std::logic_error);
}

// Поиск в пустом дереве вызывает исключение
TEST_F(BSTreeTest, FindInEmptyTreeThrows) {
    EXPECT_THROW(tree.find(1), std::logic_error);
}

// ==================== BSTree Erase Tests ====================

// Удаление единственного элемента
TEST_F(BSTreeTest, EraseSingleElement) {
    tree.insert(5, "five");
    tree.erase(5);
    EXPECT_TRUE(tree.is_empty());
}

// Удаление корня с двумя потомками
TEST_F(BSTreeTest, EraseRootWithTwoChildren) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.erase(5);
    EXPECT_TRUE(tree.find(3) == "three");
    EXPECT_TRUE(tree.find(7) == "seven");
}

// Удаление корня с левым потомком
TEST_F(BSTreeTest, EraseRootWithLeftChild) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.erase(5);
    EXPECT_TRUE(tree.find(3) == "three");
}

// Удаление корня с правым потомком
TEST_F(BSTreeTest, EraseRootWithRightChild) {
    tree.insert(5, "five");
    tree.insert(7, "seven");
    tree.erase(5);
    EXPECT_TRUE(tree.find(7) == "seven");
}

// Удаление листового узла
TEST_F(BSTreeTest, EraseLeafNode) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.erase(3);
    EXPECT_THROW(tree.find(3), std::logic_error);
    EXPECT_TRUE(tree.find(5) == "five");
    EXPECT_TRUE(tree.find(7) == "seven");
}

// Удаление узла с двумя потомками (внутреннее удаление)
TEST_F(BSTreeTest, EraseNodeWithTwoChildren) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(6, "six");
    tree.insert(8, "eight");
    tree.erase(7);
    EXPECT_THROW(tree.find(7), std::logic_error);
    EXPECT_TRUE(tree.find(5) == "five");
    EXPECT_TRUE(tree.find(8) == "eight");
}

// Удаление левого потомка корня
TEST_F(BSTreeTest, EraseLeftChild) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.erase(3);
    EXPECT_THROW(tree.find(3), std::logic_error);
}

// Удаление правого потомка корня
TEST_F(BSTreeTest, EraseRightChild) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.erase(7);
    EXPECT_THROW(tree.find(7), std::logic_error);
}

// Удаление несуществующего ключа вызывает исключение
TEST_F(BSTreeTest, EraseNonexistentKeyThrows) {
    tree.insert(5, "five");
    EXPECT_THROW(tree.erase(99), std::logic_error);
}

// Удаление из пустого дерева вызывает исключение
TEST_F(BSTreeTest, EraseFromEmptyTreeThrows) {
    EXPECT_THROW(tree.erase(1), std::logic_error);
}

// Удаление всех элементов по одному
TEST_F(BSTreeTest, EraseAllElementsOneByOne) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");
    tree.insert(6, "six");
    tree.insert(8, "eight");

    tree.erase(2);
    tree.erase(4);
    tree.erase(6);
    tree.erase(8);
    tree.erase(3);
    tree.erase(7);
    tree.erase(5);

    EXPECT_TRUE(tree.is_empty());
}

// ==================== BSTree to_string Tests ====================

// to_string на пустом дереве
TEST_F(BSTreeTest, ToStringEmptyTree) {
    std::string result = tree.to_string();
    EXPECT_TRUE(result.empty());
}

// to_string на одном элементе
TEST_F(BSTreeTest, ToStringSingleElement) {
    tree.insert(5, "five");
    std::string result = tree.to_string();
    EXPECT_TRUE(result.find("5:five") != std::string::npos);
}

// to_string преобразует все элементы (префиксный порядок)
TEST_F(BSTreeTest, ToStringAllElements) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    std::string result = tree.to_string();
    EXPECT_TRUE(result.find("5:five") != std::string::npos);
    EXPECT_TRUE(result.find("3:three") != std::string::npos);
    EXPECT_TRUE(result.find("7:seven") != std::string::npos);
}

// to_string возвращает префиксный порядок (корень первым)
TEST_F(BSTreeTest, ToStringPrefixOrder) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    std::string result = tree.to_string();
    size_t pos5 = result.find("5:five");
    size_t pos3 = result.find("3:three");
    size_t pos7 = result.find("7:seven");
    EXPECT_TRUE(pos5 < pos3 && pos5 < pos7);
}

// ==================== BSTree to_string_sorted Tests ====================

// to_string_sorted на пустом дереве
TEST_F(BSTreeTest, ToStringSortedEmptyTree) {
    std::string result = tree.to_string_sorted();
    EXPECT_TRUE(result.empty());
}

// to_string_sorted на одном элементе
TEST_F(BSTreeTest, ToStringSortedSingleElement) {
    tree.insert(5, "five");
    std::string result = tree.to_string_sorted();
    EXPECT_TRUE(result.find("5:five") != std::string::npos);
}

// to_string_sorted возвращает элементы в отсортированном порядке (инфиксный обход)
TEST_F(BSTreeTest, ToStringSortedInOrder) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(9, "nine");
    std::string result = tree.to_string_sorted();
    size_t pos1 = result.find("1:one");
    size_t pos3 = result.find("3:three");
    size_t pos5 = result.find("5:five");
    size_t pos7 = result.find("7:seven");
    size_t pos9 = result.find("9:nine");
    EXPECT_TRUE(pos1 < pos3 && pos3 < pos5 && pos5 < pos7 && pos7 < pos9);
}

// ==================== BSTree Edge Cases ====================

// Дерево с отрицательными ключами
TEST_F(BSTreeTest, NegativeKeys) {
    tree.insert(-5, "minus five");
    tree.insert(-3, "minus three");
    tree.insert(-7, "minus seven");
    EXPECT_EQ(tree.find(-5), "minus five");
    EXPECT_EQ(tree.find(-3), "minus three");
    EXPECT_EQ(tree.find(-7), "minus seven");
}

// Дерево с нулевым ключом
TEST_F(BSTreeTest, ZeroKey) {
    tree.insert(0, "zero");
    tree.insert(-1, "minus one");
    tree.insert(1, "one");
    EXPECT_EQ(tree.find(0), "zero");
}

// Большое дерево
TEST_F(BSTreeTest, LargeTree) {
    for (int i = 0; i < 100; ++i) {
        tree.insert(i, "value_" + std::to_string(i));
    }
    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(tree.find(50), "value_50");
    EXPECT_EQ(tree.find(0), "value_0");
    EXPECT_EQ(tree.find(99), "value_99");
}

// Линейное дерево (все вставки в порядке возрастания)
TEST_F(BSTreeTest, LinearTreeAscending) {
    for (int i = 1; i <= 10; ++i) {
        tree.insert(i, "val_" + std::to_string(i));
    }
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(tree.find(i), "val_" + std::to_string(i));
    }
}

// Линейное дерево (все вставки в порядке убывания)
TEST_F(BSTreeTest, LinearTreeDescending) {
    for (int i = 10; i >= 1; --i) {
        tree.insert(i, "val_" + std::to_string(i));
    }
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(tree.find(i), "val_" + std::to_string(i));
    }
}

// ==================== BSTree Type Tests ====================

// Строковые ключи и целые значения
TEST(BSTreeTypesTest, StringKeyIntValue) {
    BSTree<std::string, int> tree;
    tree.insert("apple", 1);
    tree.insert("banana", 2);
    tree.insert("cherry", 3);
    EXPECT_EQ(tree.find("apple"), 1);
    EXPECT_EQ(tree.find("banana"), 2);
    EXPECT_EQ(tree.find("cherry"), 3);
}

// Double ключи и строковые значения
TEST(BSTreeTypesTest, DoubleKeyStringValue) {
    BSTree<double, std::string> tree;
    tree.insert(3.14, "pi");
    tree.insert(2.71, "e");
    tree.insert(1.41, "sqrt2");
    EXPECT_EQ(tree.find(1.41), "sqrt2");
    EXPECT_EQ(tree.find(2.71), "e");
    EXPECT_EQ(tree.find(3.14), "pi");
}

// ==================== BSTree Complex Operations ====================

// Комбинированные операции: вставка, поиск, удаление
TEST_F(BSTreeTest, ComplexOperations) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");
    tree.insert(6, "six");
    tree.insert(8, "eight");

    EXPECT_EQ(tree.find(4), "four");
    tree.erase(4);
    EXPECT_THROW(tree.find(4), std::logic_error);

    tree.insert(4, "four_new");
    EXPECT_EQ(tree.find(4), "four_new");
}

// Удаление и повторная вставка
TEST_F(BSTreeTest, EraseAndReinsert) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.erase(5);
    tree.insert(5, "FIVE");
    EXPECT_EQ(tree.find(5), "FIVE");
}

// Узел-преемник имеет правого потомка
TEST_F(BSTreeTest, EraseNodeWithSuccessorHavingRightChild) {
    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");
    tree.insert(12, "twelve");
    tree.insert(20, "twenty");
    tree.insert(18, "eighteen");
    tree.insert(17, "seventeen");
    
    // Удаляем 15: у его преемника 18 есть левый потомок 17 и правый 20
    tree.erase(15);
    
    EXPECT_THROW(tree.find(15), std::logic_error);
    EXPECT_EQ(tree.find(18), "eighteen");
    EXPECT_EQ(tree.find(20), "twenty");
}

// Множественные удаления с проверкой целостности
TEST_F(BSTreeTest, MultipleErasesWithIntegrityCheck) {
    for (int i = 1; i <= 15; ++i) {
        tree.insert(i, "val_" + std::to_string(i));
    }

    tree.erase(8);
    tree.erase(4);
    tree.erase(12);

    // Проверяем оставшиеся элементы
    for (int i = 1; i <= 15; ++i) {
        if (i == 4 || i == 8 || i == 12) {
            EXPECT_THROW(tree.find(i), std::logic_error);
        } else {
            EXPECT_EQ(tree.find(i), "val_" + std::to_string(i));
        }
    }
}

// Проверка структуры после операций
TEST_F(BSTreeTest, TreeStructureAfterOperations) {
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");
    tree.insert(6, "six");
    tree.insert(8, "eight");

    std::string before = tree.to_string_sorted();
    
    tree.erase(2);
    tree.insert(2, "two_new");
    
    // После удаления и вставки элемента остальная структура должна сохраниться
    EXPECT_EQ(tree.find(5), "five");
    EXPECT_EQ(tree.find(3), "three");
}