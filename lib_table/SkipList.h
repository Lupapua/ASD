#include <utility>
#include <iostream>
#include <cstdlib>   
#include "../lib_list/List.h"

template <typename Tkey, typename Tvalue>
struct SkipNode {
	std::pair<Tkey, Tvalue> data;
	size_t lvls;
	SkipNode<Tkey, Tvalue>** next;

	SkipNode(const Tkey& key, const Tvalue& value, size_t levels = 1) : data(std::pair<Tkey, Tvalue>(key, value)), lvls(levels), next(nullptr)
	{
		if (lvls > 0) {
			next = new SkipNode<Tkey, Tvalue>* [lvls];
			for (size_t i = 0; i < lvls; ++i) next[i] = nullptr;
		}
	}
	bool is_empty() const noexcept {
		return data.first == Tkey() && data.second == Tvalue();
	}
	~SkipNode() {
		delete[] next;
	}
};

template <typename Tkey, typename Tvalue>
class SkipList {
	List< SkipNode<Tkey, Tvalue>* > heads;
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
	SkipNode<Tkey, Tvalue>* new_node = new SkipNode<Tkey, Tvalue>(key, value, new_lvl);

	bool was_empty = is_empty();
	size_t heads_count = heads.size();

	if (heads_count < new_lvl) {
		for (size_t i = heads_count; i < new_lvl; ++i) {
			heads.push_back(nullptr);
		}
		heads_count = heads.size();
	}

	if (was_empty) {
		for (size_t level = 0; level < new_lvl; ++level) {
			Node< SkipNode<Tkey, Tvalue>* >* hn = heads.begin();
			size_t idx = 0;
			while (hn != nullptr && idx < level) { hn = hn->next; ++idx; }
			if (hn != nullptr) {
				hn->value = new_node;
			}
		}
		if (new_lvl > lvl) lvl = new_lvl;
		return;
	}

	{
		Node< SkipNode<Tkey, Tvalue>* >* hn0 = heads.begin();
		SkipNode<Tkey, Tvalue>* cur = nullptr;
		if (hn0 != nullptr) cur = hn0->value;
		while (cur != nullptr && cur->data.first < key) {
			cur = cur->next[0];
		}
		if (cur != nullptr && cur->data.first == key) {
			cur->data.second = value;
			delete new_node;
			return;
		}
	}

	for (size_t level = 0; level < new_lvl; ++level) {
		Node< SkipNode<Tkey, Tvalue>* >* hn = heads.begin();
		size_t idx = 0;
		while (hn != nullptr && idx < level) { hn = hn->next; ++idx; }
		SkipNode<Tkey, Tvalue>* headPtr = nullptr;
		if (hn != nullptr) headPtr = hn->value;

		if (headPtr == nullptr || key < headPtr->data.first) {
			new_node->next[level] = headPtr;
			if (hn != nullptr) {
				hn->value = new_node;
			}
			else {
				heads.push_back(new_node);
			}
			continue;
		}

		SkipNode<Tkey, Tvalue>* prev = headPtr;
		SkipNode<Tkey, Tvalue>* cur = headPtr->next[level];
		while (cur != nullptr && cur->data.first < key) {
			prev = cur;
			cur = cur->next[level];
		}

		new_node->next[level] = cur;
		prev->next[level] = new_node;
	}

	if (new_lvl > lvl) lvl = new_lvl;
}