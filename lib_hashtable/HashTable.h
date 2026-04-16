#pragma once
#include <iostream>
#include "../lib_table/ITable.h"
#include "../lib_list/List.h"
#include "../lib_tvector/TVector.h"

template <typename Tvalue>
class HashTableC : public ITable<std::string, Tvalue> {
private:
	TVector<List<std::pair<std::string, Tvalue>>> _rows;

	size_t h(const std::string& key) const noexcept {
		size_t hashvalue = 0;
		for(auto sym: key) {
			hashvalue = (hashvalue + sym) % _rows.size();
		}
		return hashvalue;
	}
public:
	HashTableC(size_t capacity = 16) : _rows(capacity) {}
	~HashTableC() {}
	void insert(const std::string& key, const Tvalue& val) override;
	Tvalue find(const std::string& key) const override;
	void erase(const std::string& key) override;
	bool consist(const std::string& key) const noexcept override;
	void merge(const HashTableC<Tvalue>& other);
	std::ostream& print(std::ostream& out) const noexcept override {
		return out;
	}

	bool is_empty() const noexcept override {
		return false;
	}
};

template <typename Tvalue>
void HashTableC<Tvalue>::insert(const std::string& key, const Tvalue& val) {
	std::pair<std::string, Tvalue> new_data = { key, val };
	size_t index = h(key);
	for (auto it = _rows[index].begin_iter(); it != _rows[index].end_iter(); it++) {
		if (it->first == key) {
			it->second = val; 
			return;
		}
	}

	_rows[index].push_back({ key, val });
}

template <typename Tvalue>
void HashTableC<Tvalue>::erase(const std::string& key) {
	size_t index = h(key);
	size_t pos = 0;
	for (auto it = _rows[index].begin_iter(); it != _rows[index].end_iter(); it++) {
		if (it->first == key) {
			_rows[index].erase(pos);
			return;
		}
		pos++;
	}
}

template <typename Tvalue>
Tvalue HashTableC<Tvalue>::find(const std::string& key) const {
	size_t index = h(key);
	for (auto it = _rows[index].begin_iter(); it != _rows[index].end_iter(); it++) {
		if (it->first == key) {
			return it->second;
		}
	}
	throw std::runtime_error("Key not found");
}

template <typename Tvalue>
bool HashTableC<Tvalue>::consist(const std::string& key) const noexcept {
	size_t index = h(key);
	for (auto it = _rows[index].begin_iter(); it != _rows[index].end_iter(); it++) {
		if (it->first == key) {
			return true;
		}
	}
	return false;
}

template <typename Tvalue>
void HashTableC<Tvalue> :: merge(const HashTableC<Tvalue>& other) {
	for (size_t i = 0; i < other._rows.size(); ++i) {
		auto it = other._rows[i].begin_iter();
		auto end = other._rows[i].end_iter();
		while (it != end) {
			this->insert(it->first, it->second);
			++it;
		}
	}
}