#include <gtest/gtest.h>
#include "../lib_DSU/DSU.h"

int count_islands(std::vector<std::vector<int>>& field) {
	if (field.empty()) { return 0; }
	int rows = field.size();
	int cols = field[0].size();
	DSU dsu(rows * cols);
	int islandCount = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (field[i][j] == 1) {
				islandCount++;
				if (j + 1 < cols && field[i][j + 1] == 1) {
					if (dsu.find(i * cols + j) != dsu.find(i * cols + (j + 1))) {
						dsu.unite(i * cols + j, i * cols + (j + 1));
						islandCount--;
					}
				}
				if (i + 1 < rows && field[i + 1][j] == 1) {
					if (dsu.find(i * cols + j) != dsu.find((i + 1) * cols + j)) {
						dsu.unite(i * cols + j, (i + 1) * cols + j);
						islandCount--;
					}
				}
			}
		}
	}
	return islandCount;
}

TEST(DSUTest, EasyExample) {
	std::vector<std::vector<int>> field = {
		{1, 1, 0, 0, 0},
		{1, 0, 0, 1, 1},
		{0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0},
		{1, 1, 0, 0, 1}
	};

	int expected_island_count = 4;
	int actual_island_count = count_islands(field);

	EXPECT_EQ(actual_island_count, expected_island_count);
}
