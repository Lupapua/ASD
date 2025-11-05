#pragma	once

#include <iostream>

class DSU {
	int* _parent;
	int _size;
	int* _rank;
public:
	DSU(int);
	~DSU();
	int find(int);
	void unite(int, int);
};
