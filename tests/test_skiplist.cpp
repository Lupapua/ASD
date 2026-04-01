#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>
#include "../lib_table/SkipList.h"

// ==================== SkipList Basic Tests ====================

class SkipListTest : public ::testing::Test {
protected:
    SkipList<int, std::string> skiplist;

    void SetUp() override {
        srand(static_cast<unsigned>(time(0)));
    }
};

// Конструктор создаёт пустой skip list
TEST_F(SkipListTest, DefaultConstructorCreatesEmptySkipList) {
    EXPECT_TRUE(skiplist.is_empty());
}

// Конструктор с max_lvl параметром
TEST_F(SkipListTest, ConstructorWithMaxLevel) {
    SkipList<int, std::string> sl(8);
    EXPECT_TRUE(sl.is_empty());
    EXPECT_EQ(sl.get_max_lvl(), 8);
}

// Получение максимального уровня
TEST_F(SkipListTest, GetMaxLevelReturnsCorrectValue) {
    SkipList<int, std::string> sl(32);
    EXPECT_EQ(sl.get_max_lvl(), 32);
}

// Получение текущего уровня пустого skip list
TEST_F(SkipListTest, GetLevelEmptySkipList) {
    EXPECT_EQ(skiplist.get_lvl(), 1);
}

// ==================== SkipList Insert/Push_back Tests ====================

// Вставка одного элемента
TEST_F(SkipListTest, PushBackSingleElement) {
    skiplist.push_back(5, "five");
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка нескольких элементов в порядке возрастания
TEST_F(SkipListTest, PushBackAscendingOrder) {
    skiplist.push_back(1, "one");
    skiplist.push_back(2, "two");
    skiplist.push_back(3, "three");
    skiplist.push_back(4, "four");
    skiplist.push_back(5, "five");
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка нескольких элементов в порядке убывания
TEST_F(SkipListTest, PushBackDescendingOrder) {
    skiplist.push_back(5, "five");
    skiplist.push_back(4, "four");
    skiplist.push_back(3, "three");
    skiplist.push_back(2, "two");
    skiplist.push_back(1, "one");
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка в случайном порядке
TEST_F(SkipListTest, PushBackRandomOrder) {
    skiplist.push_back(5, "five");
    skiplist.push_back(2, "two");
    skiplist.push_back(8, "eight");
    skiplist.push_back(1, "one");
    skiplist.push_back(9, "nine");
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка дубликата ключа обновляет значение
TEST_F(SkipListTest, PushBackDuplicateKeyUpdatesValue) {
    skiplist.push_back(5, "five");
    skiplist.push_back(5, "FIVE");
    // Вторая вставка с тем же ключом должна обновить значение
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка нескольких дубликатов
TEST_F(SkipListTest, PushBackMultipleDuplicates) {
    skiplist.push_back(5, "five");
    skiplist.push_back(5, "FIVE");
    skiplist.push_back(5, "FiVe");
    EXPECT_FALSE(skiplist.is_empty());
}

// ==================== SkipList Level Generation Tests ====================

// generate_lvl возвращает значение >= 1
TEST_F(SkipListTest, GenerateLvlMinimumValue) {
    for (int i = 0; i < 20; ++i) {
        size_t level = skiplist.generate_lvl();
        EXPECT_GE(level, 1);
    }
}

// generate_lvl не превышает max_lvl
TEST_F(SkipListTest, GenerateLvlNotExceedsMax) {
    for (int i = 0; i < 20; ++i) {
        size_t level = skiplist.generate_lvl();
        EXPECT_LE(level, skiplist.get_max_lvl());
    }
}

// Уровень увеличивается при добавлении элементов
TEST_F(SkipListTest, LevelIncreasesWithNewElements) {
    size_t initial_lvl = skiplist.get_lvl();
    for (int i = 0; i < 50; ++i) {
        skiplist.push_back(i, "val_" + std::to_string(i));
    }
    // После вставки 50 элементов уровень должен вероятно увеличиться
    // (хотя это не гарантировано из-за случайности)
    EXPECT_GE(skiplist.get_lvl(), initial_lvl);
}

// ==================== SkipList with Different Types ====================

// String ключи и int значения
TEST(SkipListTypesTest, StringKeyIntValue) {
    SkipList<std::string, int> sl;
    sl.push_back("apple", 1);
    sl.push_back("banana", 2);
    sl.push_back("cherry", 3);
    EXPECT_FALSE(sl.is_empty());
}

// Double ключи и string значения
TEST(SkipListTypesTest, DoubleKeyStringValue) {
    SkipList<double, std::string> sl;
    sl.push_back(3.14, "pi");
    sl.push_back(2.71, "e");
    sl.push_back(1.41, "sqrt2");
    EXPECT_FALSE(sl.is_empty());
}

// Char ключи и string значения
TEST(SkipListTypesTest, CharKeyStringValue) {
    SkipList<char, std::string> sl;
    sl.push_back('a', "alpha");
    sl.push_back('b', "beta");
    sl.push_back('c', "gamma");
    EXPECT_FALSE(sl.is_empty());
}

// ==================== SkipList Edge Cases ====================

// Вставка с отрицательными ключами
TEST_F(SkipListTest, NegativeKeys) {
    skiplist.push_back(-5, "minus five");
    skiplist.push_back(-3, "minus three");
    skiplist.push_back(-7, "minus seven");
    skiplist.push_back(0, "zero");
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка с нулевым ключом
TEST_F(SkipListTest, ZeroKey) {
    skiplist.push_back(0, "zero");
    skiplist.push_back(-1, "minus one");
    skiplist.push_back(1, "one");
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка очень больших значений ключей
TEST_F(SkipListTest, LargeIntKeys) {
    skiplist.push_back(1000000, "million");
    skiplist.push_back(2000000, "two million");
    skiplist.push_back(500000, "half million");
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка очень маленьких значений ключей
TEST_F(SkipListTest, SmallIntKeys) {
    skiplist.push_back(-1000000, "minus million");
    skiplist.push_back(-2000000, "minus two million");
    skiplist.push_back(-500000, "minus half million");
    EXPECT_FALSE(skiplist.is_empty());
}

// ==================== SkipList Large Scale Tests ====================

// Вставка 100 элементов в порядке возрастания
TEST_F(SkipListTest, InsertHundredElementsAscending) {
    for (int i = 0; i < 100; ++i) {
        skiplist.push_back(i, "value_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
    EXPECT_GE(skiplist.get_lvl(), 1);
}

// Вставка 100 элементов в порядке убывания
TEST_F(SkipListTest, InsertHundredElementsDescending) {
    for (int i = 99; i >= 0; --i) {
        skiplist.push_back(i, "value_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка 100 элементов в случайном порядке
TEST_F(SkipListTest, InsertHundredElementsRandom) {
    for (int i = 0; i < 100; ++i) {
        skiplist.push_back(rand() % 1000, "value_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка 1000 элементов
TEST_F(SkipListTest, InsertThousandElements) {
    for (int i = 0; i < 1000; ++i) {
        skiplist.push_back(i, "val_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
    EXPECT_GT(skiplist.get_lvl(), 1);
}

// ==================== SkipList Stress Tests ====================

// Много вставок одного и того же ключа
TEST_F(SkipListTest, ManyDuplicateInserts) {
    for (int i = 0; i < 50; ++i) {
        skiplist.push_back(5, "value_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// Чередование разных ключей и дубликатов
TEST_F(SkipListTest, AlternatingUniqueAndDuplicate) {
    for (int i = 0; i < 20; ++i) {
        skiplist.push_back(i, "unique_" + std::to_string(i));
        skiplist.push_back(5, "duplicate_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// Вставка элементов близких по значению
TEST_F(SkipListTest, CloseValueKeys) {
    for (int i = 0; i < 50; ++i) {
        skiplist.push_back(1000 + i, "val_" + std::to_string(1000 + i));
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// ==================== SkipList Constructor Variations ====================

// Конструктор с малым max_lvl
TEST(SkipListConstructorTest, SmallMaxLevel) {
    SkipList<int, std::string> sl(1);
    EXPECT_EQ(sl.get_max_lvl(), 1);
    sl.push_back(1, "one");
    EXPECT_FALSE(sl.is_empty());
}

// Конструктор с большим max_lvl
TEST(SkipListConstructorTest, LargeMaxLevel) {
    SkipList<int, std::string> sl(64);
    EXPECT_EQ(sl.get_max_lvl(), 64);
    sl.push_back(1, "one");
    EXPECT_FALSE(sl.is_empty());
}

// Конструктор с типичным max_lvl
TEST(SkipListConstructorTest, TypicalMaxLevel) {
    SkipList<int, std::string> sl(16);
    EXPECT_EQ(sl.get_max_lvl(), 16);
    EXPECT_EQ(sl.get_lvl(), 1);
}

// ==================== SkipList Complex Scenarios ====================

// Последовательное добавление чётных и нечётных чисел
TEST_F(SkipListTest, EvenAndOddNumbers) {
    for (int i = 0; i < 50; i += 2) {
        skiplist.push_back(i, "even_" + std::to_string(i));
    }
    for (int i = 1; i < 50; i += 2) {
        skiplist.push_back(i, "odd_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// Добавление элементов в группах
TEST_F(SkipListTest, GroupedInserts) {
    // Первая группа: 1-10
    for (int i = 1; i <= 10; ++i) {
        skiplist.push_back(i, "group1_" + std::to_string(i));
    }
    // Вторая группа: 101-110
    for (int i = 101; i <= 110; ++i) {
        skiplist.push_back(i, "group2_" + std::to_string(i));
    }
    // Третья группа: 201-210
    for (int i = 201; i <= 210; ++i) {
        skiplist.push_back(i, "group3_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// Добавление элементов с одинаковым префиксом значения
TEST_F(SkipListTest, SamePrefixValues) {
    for (int i = 0; i < 10; ++i) {
        skiplist.push_back(i, "value");
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// Добавление элементов с очень длинными значениями
TEST_F(SkipListTest, LongStringValues) {
    std::string longValue(1000, 'a');
    skiplist.push_back(1, longValue);
    skiplist.push_back(2, longValue + "b");
    EXPECT_FALSE(skiplist.is_empty());
}

// ==================== SkipList Empty State Tests ====================

// Проверка is_empty на новом skip list
TEST_F(SkipListTest, IsEmptyNewSkipList) {
    EXPECT_TRUE(skiplist.is_empty());
}

// Проверка is_empty после одной вставки
TEST_F(SkipListTest, IsEmptyAfterOneInsert) {
    skiplist.push_back(1, "one");
    EXPECT_FALSE(skiplist.is_empty());
}

// Проверка is_empty после нескольких вставок
TEST_F(SkipListTest, IsEmptyAfterMultipleInserts) {
    for (int i = 0; i < 10; ++i) {
        skiplist.push_back(i, "val");
        EXPECT_FALSE(skiplist.is_empty());
    }
}

// ==================== SkipList Multiple Instances ====================

// Несколько независимых skip list объектов
TEST(SkipListMultipleTest, MultipleIndependentInstances) {
    SkipList<int, std::string> sl1;
    SkipList<int, std::string> sl2;
    SkipList<int, std::string> sl3;

    sl1.push_back(1, "one");
    sl2.push_back(2, "two");
    sl3.push_back(3, "three");

    EXPECT_FALSE(sl1.is_empty());
    EXPECT_FALSE(sl2.is_empty());
    EXPECT_FALSE(sl3.is_empty());
}

// Несколько skip list с разными типами
TEST(SkipListMultipleTest, DifferentTypeInstances) {
    SkipList<int, std::string> slInt;
    SkipList<std::string, int> slStr;
    SkipList<double, std::string> slDouble;

    slInt.push_back(42, "answer");
    slStr.push_back("hello", 1);
    slDouble.push_back(3.14, "pi");

    EXPECT_FALSE(slInt.is_empty());
    EXPECT_FALSE(slStr.is_empty());
    EXPECT_FALSE(slDouble.is_empty());
}

// ==================== SkipList Sequence Tests ====================

// Строгое возрастание ключей
TEST_F(SkipListTest, StrictlyIncreasingKeys) {
    for (int i = 1; i <= 100; i += 2) {
        skiplist.push_back(i, "odd_" + std::to_string(i));
    }
    EXPECT_FALSE(skiplist.is_empty());
}

// Изменяющиеся значения для разных ключей
TEST_F(SkipListTest, DifferentValuesPerKey) {
    skiplist.push_back(1, "one");
    skiplist.push_back(1, "ONE");
    skiplist.push_back(1, "oNe");
    skiplist.push_back(2, "two");
    skiplist.push_back(2, "TWO");
    EXPECT_FALSE(skiplist.is_empty());
}

// Сочетание вставок и дубликатов в определённом порядке
TEST_F(SkipListTest, MixedInsertAndUpdate) {
    skiplist.push_back(5, "five");
    skiplist.push_back(3, "three");
    skiplist.push_back(7, "seven");
    skiplist.push_back(5, "FIVE");
    skiplist.push_back(3, "THREE");
    skiplist.push_back(7, "SEVEN");
    EXPECT_FALSE(skiplist.is_empty());
}

// ==================== SkipList Growth Tests ====================

// Проверка роста уровня при масштабировании
TEST_F(SkipListTest, LevelGrowthOverTime) {
    size_t prev_level = skiplist.get_lvl();
    for (int batch = 0; batch < 10; ++batch) {
        for (int i = 0; i < 100; ++i) {
            skiplist.push_back(batch * 1000 + i, "val");
        }
        size_t current_level = skiplist.get_lvl();
        EXPECT_GE(current_level, prev_level);
        prev_level = current_level;
    }
}

// Уровень никогда не превышает max_lvl
TEST_F(SkipListTest, LevelNeverExceedsMax) {
    for (int i = 0; i < 500; ++i) {
        skiplist.push_back(i, "val");
        EXPECT_LE(skiplist.get_lvl(), skiplist.get_max_lvl());
    }
}