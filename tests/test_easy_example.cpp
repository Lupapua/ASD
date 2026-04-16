#include <gtest/gtest.h>
#include <iostream>
#include "HashTable.h"

TEST(HashTableMergeTest, MergeTwoTables) {
    // 1. Подготовка первой таблицы
    HashTableC<int> table1(10);
    table1.insert("alpha", 1);
    table1.insert("beta", 2);

    // 2. Подготовка второй таблицы
    HashTableC<int> table2(10);
    table2.insert("beta", 20);  // Ключ совпадает, значение должно обновиться
    table2.insert("gamma", 3);  // Новый ключ

    // 3. Выполнение объединения
    table1.merge(table2);

    // 4. Проверки (Assertions)

    // Проверяем, что старый уникальный ключ остался
    EXPECT_TRUE(table1.consist("alpha"));
    EXPECT_EQ(table1.find("alpha"), 1);

    // Проверяем, что общее значение обновилось значением из второй таблицы
    EXPECT_TRUE(table1.consist("beta"));
    EXPECT_EQ(table1.find("beta"), 20);

    // Проверяем, что новый ключ добавился
    EXPECT_TRUE(table1.consist("gamma"));
    EXPECT_EQ(table1.find("gamma"), 3);
}

TEST(HashTableMergeTest, MergeEmptyTable) {
    HashTableC<int> table1(10);
    table1.insert("key", 100);

    HashTableC<int> emptyTable(10);

    table1.merge(emptyTable);

    EXPECT_EQ(table1.find("key"), 100);
    // Тут можно добавить проверку на размер, если у тебя есть метод size()
}