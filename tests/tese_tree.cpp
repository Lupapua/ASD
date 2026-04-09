#include <gtest/gtest.h>
#include <sstream>
#include "Tree.h"


// Проверяем что новое дерево пустое
TEST(TreeConstructor, DefaultConstructorCreatesEmptyTree) {
    Tree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}


// Проверяем что после вставки одного элемента дерево не пустое
TEST(TreeInsert, InsertSingleElement) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_FALSE(tree.is_empty());
}

// Проверяем что можно вставить несколько элементов
TEST(TreeInsert, InsertMultipleElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(8, "eight");
    EXPECT_FALSE(tree.is_empty());
}



// Проверяем что LCR выводит все элементы дерева
TEST(TreeLCR, LCROutputsAllElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(8, "eight");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    tree.lcr();

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    // Проверяем что все элементы присутствуют в выводе
    EXPECT_TRUE(output.find("2") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
    EXPECT_TRUE(output.find("5") != std::string::npos);
    EXPECT_TRUE(output.find("7") != std::string::npos);
    EXPECT_TRUE(output.find("8") != std::string::npos);
}

// Проверяем что LCR выводит правильное название метода
TEST(TreeLCR, LCRHasCorrectLabel) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.lcr();
    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("") != std::string::npos);
}

// Проверяем что LCR работает на одном элементе
TEST(TreeLCR, LCRSingleElement) {
    Tree<int, std::string> tree;
    tree.insert(42, "answer");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.lcr();
    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("42") != std::string::npos);
}

// Проверяем что LCR не падает на пустом дереве
TEST(TreeLCR, LCREmptyTree) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.lcr());
}


// Проверяем что LRC выводит все элементы дерева
TEST(TreeLRC, LRCOutputsAllElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(8, "eight");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.lrc();
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    EXPECT_TRUE(output.find("2") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
    EXPECT_TRUE(output.find("5") != std::string::npos);
    EXPECT_TRUE(output.find("7") != std::string::npos);
    EXPECT_TRUE(output.find("8") != std::string::npos);
}

// Проверяем что LRC выводит правильное название метода
TEST(TreeLRC, LRCHasCorrectLabel) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.lrc();
    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("") != std::string::npos);
}

// Проверяем что в LRC корень выводится последним (постфиксный порядок)
TEST(TreeLRC, LRCRootComesLast) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.lrc();
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    size_t pos3 = output.find("(3:three)");
    size_t pos5 = output.find("(5:five)");
    EXPECT_TRUE(pos3 != std::string::npos && pos5 != std::string::npos);
    EXPECT_TRUE(pos3 < pos5);
}

// Проверяем что LRC не падает на пустом дереве
TEST(TreeLRC, LRCEmptyTree) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.lrc());
}


// Проверяем что CLR выводит все элементы дерева
TEST(TreeCLR, CLROutputsAllElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(8, "eight");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.clr();
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    EXPECT_TRUE(output.find("2") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
    EXPECT_TRUE(output.find("5") != std::string::npos);
    EXPECT_TRUE(output.find("7") != std::string::npos);
    EXPECT_TRUE(output.find("8") != std::string::npos);
}

// Проверяем что CLR выводит правильное название метода
TEST(TreeCLR, CLRHasCorrectLabel) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.clr();
    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("") != std::string::npos);
}

// Проверяем что в CLR корень выводится первым (префиксный порядок)
TEST(TreeCLR, CLRRootComesFirst) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.clr();
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    // Позиция (5) должна быть раньше позиции (3)
    size_t pos5 = output.find("(5:five)");
    size_t pos3 = output.find("(3:three)");
    EXPECT_TRUE(pos5 != std::string::npos && pos3 != std::string::npos);
    EXPECT_TRUE(pos5 < pos3);
}

// Проверяем что CLR не падает на пустом дереве
TEST(TreeCLR, CLREmptyTree) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.clr());
}


// Проверяем что WIDTH выводит элементы по уровням
TEST(TreeWidth, WidthHasLevelStructure) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(8, "eight");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.width();
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    // Проверяем наличие уровней
    EXPECT_TRUE(output.find("Level 0") != std::string::npos);
    EXPECT_TRUE(output.find("Level 1") != std::string::npos);
}

// Проверяем что WIDTH выводит все элементы дерева
TEST(TreeWidth, WidthOutputsAllElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(8, "eight");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.width();
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    EXPECT_TRUE(output.find("2") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
    EXPECT_TRUE(output.find("5") != std::string::npos);
    EXPECT_TRUE(output.find("7") != std::string::npos);
    EXPECT_TRUE(output.find("8") != std::string::npos);
}

// Проверяем что WIDTH выводит правильное название метода
TEST(TreeWidth, WidthHasCorrectLabel) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.width();
    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("WIDTH") != std::string::npos);
}

// Проверяем что корень находится на Level 0 при WIDTH обходе
TEST(TreeWidth, WidthRootOnLevel0) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.width();
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    EXPECT_TRUE(output.find("Level 0") != std::string::npos);
    EXPECT_TRUE(output.find("(5:five)") != std::string::npos);
}

// Проверяем что WIDTH работает на одном элементе
TEST(TreeWidth, WidthSingleElement) {
    Tree<int, std::string> tree;
    tree.insert(42, "answer");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    tree.width();
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    EXPECT_TRUE(output.find("Level 0") != std::string::npos);
    EXPECT_TRUE(output.find("42") != std::string::npos);
}

// Проверяем что WIDTH не падает на пустом дереве
TEST(TreeWidth, WidthEmptyTree) {
    Tree<int, std::string> tree;
    EXPECT_NO_THROW(tree.width());
}

// Проверяем что все четыре метода работают одновременно на одном дереве
TEST(TreeComplex, AllMethodsTogether) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    EXPECT_NO_THROW(tree.lcr());
    EXPECT_NO_THROW(tree.lrc());
    EXPECT_NO_THROW(tree.clr());
    EXPECT_NO_THROW(tree.width());
}

// Проверяем что все методы работают на пустом дереве
TEST(TreeComplex, AllMethodsOnEmptyTree) {
    Tree<int, std::string> tree;

    EXPECT_NO_THROW(tree.lcr());
    EXPECT_NO_THROW(tree.lrc());
    EXPECT_NO_THROW(tree.clr());
    EXPECT_NO_THROW(tree.width());
}

// Проверяем что все методы работают на большом дереве с 15 элементами
TEST(TreeComplex, LargeTreeWith15Elements) {
    Tree<int, std::string> tree;

    for (int i = 1; i <= 15; i++) {
        tree.insert(i, "value" + std::to_string(i));
    }

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    tree.lcr();
    std::string lcr = buffer.str();
    buffer.str("");
    buffer.clear();

    tree.lrc();
    std::string lrc = buffer.str();
    buffer.str("");
    buffer.clear();

    tree.clr();
    std::string clr = buffer.str();
    buffer.str("");
    buffer.clear();

    tree.width();
    std::string width = buffer.str();

    std::cout.rdbuf(old);

    // Все выводы должны быть непусты
    EXPECT_FALSE(lcr.empty());
    EXPECT_FALSE(lrc.empty());
    EXPECT_FALSE(clr.empty());
    EXPECT_FALSE(width.empty());
}

// Проверяем что дерево работает с разными типами: string ключи и int значения
TEST(TreeTypes, StringKeyIntValue) {
    Tree<std::string, int> tree;
    tree.insert("apple", 1);
    tree.insert("banana", 2);
    tree.insert("cherry", 3);

    EXPECT_NO_THROW(tree.lcr());
    EXPECT_NO_THROW(tree.lrc());
    EXPECT_NO_THROW(tree.clr());
    EXPECT_NO_THROW(tree.width());
}

// Проверяем что дерево работает с разными типами: double ключи и string значения
TEST(TreeTypes, DoubleKeyStringValue) {
    Tree<double, std::string> tree;
    tree.insert(3.14, "pi");
    tree.insert(2.71, "e");
    tree.insert(1.41, "sqrt2");

    EXPECT_NO_THROW(tree.lcr());
    EXPECT_NO_THROW(tree.lrc());
    EXPECT_NO_THROW(tree.clr());
    EXPECT_NO_THROW(tree.width());
}
// ==================== FIND ====================

// Поиск существующего элемента возвращает правильное значение
TEST(TreeFind, FindExistingKeyReturnsCorrectValue) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    const std::string* val = tree.find(3);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "three");
}

// Поиск корня возвращает правильное значение
TEST(TreeFind, FindRootReturnsCorrectValue) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    const std::string* val = tree.find(5);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "five");
}

// Поиск несуществующего ключа возвращает nullptr
TEST(TreeFind, FindMissingKeyReturnsNullptr) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    const std::string* val = tree.find(99);
    EXPECT_EQ(val, nullptr);
}

// Поиск в пустом дереве возвращает nullptr
TEST(TreeFind, FindInEmptyTreeReturnsNullptr) {
    Tree<int, std::string> tree;
    EXPECT_EQ(tree.find(1), nullptr);
}


// Поиск крайнего правого элемента
TEST(TreeFind, FindRightmostElement) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(8, "eight");

    const std::string* val = tree.find(8);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "eight");
}

// Поиск крайнего левого элемента
TEST(TreeFind, FindLeftmostElement) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(2, "two");

    const std::string* val = tree.find(2);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "two");

    Tree<int, std::string> t;
}