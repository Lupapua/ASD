#include "DSU.h"
#include <iostream>
#include <vector>

DSU::DSU(int size) {
	_size = size;
	_parent = new int[size];
	_rank = new int[size];
	for (int i = 0; i < size; i++) {
		_parent[i] = i;
		_rank[i] = 0;
	}
}

DSU::~DSU() {
	delete[] _parent;
	delete[] _rank;
}

int DSU::find(int x) {
	if (_parent[x] != x){
		_parent[x] = find(_parent[x]);
	}
	return _parent[x];
}

void DSU::unite(int _x, int _y) {
	int x = find(_x);
	int y = find(_y);
	if (_rank[x] < _rank[y]) {
		_parent[x] = find(y);
	}
	else {
		if (_rank[x] == _rank[y]) {
			_rank[find(x)]++;
		}
		_parent[y] = find(x);
	}
}
