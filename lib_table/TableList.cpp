#include <utility>
#include <iostream>
#include <cstdlib>   
#include "../lib_list/List.h"

template <typename Tkey, typename Tvalue>
struct Node {
	std::pair<Tkey, Tvalue> data;
	size_t lvls;
	Node** next;

	Node(Tkey key, Tvalue value, size_t levels = 1) : data(std::pair<Tkey, Tvalue>(key, value)), lvls(levels), next(nullptr)
	{
		if (lvls > 0) {
			next = new Node*[lvls];
			for (size_t i = 0; i < lvls; ++i) next[i] = nullptr;
		}
	}
	bool is_empty() const noexcept {
		return data.first == Tkey() && data.second == Tvalue();
	}
	~Node() {
		delete[] next;
	}
};

template <typename Tkey, typename Tvalue>
class SkipList {
	List<Node*> heads;
	size_t lvl;
	size_t max_lvl;
public:
	SkipList(size_t max_lvl = 16) : lvl(1), max_lvl(max_lvl) {}
	size_t get_lvl() const noexcept { return lvl; }
	size_t get_max_lvl() const noexcept { return max_lvl; }

	size_t generate_lvl();
	bool is_empty() const noexcept;
	void push_back(const Tkey& key, const Tvalue& value);
};

template <typename Tkey, typename Tvalue>
size_t SkipList<Tkey, Tvalue>::generate_lvl() {
	size_t new_lvl = 1;
	while (rand() % 2 == 0 && new_lvl < max_lvl) {
		++new_lvl;
	}
	return new_lvl;
}

template <typename Tkey, typename Tvalue>
bool SkipList<Tkey, Tvalue>::is_empty() const noexcept {
	return heads.is_empty();
}

template <typename Tkey, typename Tvalue>
void SkipList<Tkey, Tvalue>::push_back(const Tkey& key, const Tvalue& value) {
	size_t new_lvl = generate_lvl();
	Node* new_node = new Node(key, value, new_lvl);
	if (is_empty()) {
		for (size_t i = 0; i < new_lvl; ++i) {
			heads.push_back(new_node);
		}
	}
	else {
		
	}
}