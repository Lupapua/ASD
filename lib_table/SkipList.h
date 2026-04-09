#include <utility>
#include <iostream>
#include <cstdlib>
#include <vector>   
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
	~SkipList();

	size_t get_lvl() const noexcept { return lvl; }
	size_t get_max_lvl() const noexcept { return max_lvl; }

	size_t generate_lvl();
	bool is_empty() const noexcept;
	void push_back(const Tkey& key, const Tvalue& value);
	const Tvalue* find(const Tkey& key) const;
private:
	const Node< SkipNode<Tkey, Tvalue>* >* head_node_at(size_t level) const {
		const Node< SkipNode<Tkey, Tvalue>* >* hn = heads.begin();
		size_t idx = 0;
		while (hn != nullptr && idx < level) { hn = hn->next; ++idx; }
		return hn;
	}
	Node< SkipNode<Tkey, Tvalue>* >* head_node_at_mutable(size_t level) {
		Node< SkipNode<Tkey, Tvalue>* >* hn = heads.begin();
		size_t idx = 0;
		while (hn != nullptr && idx < level) { hn = hn->next; ++idx; }
		return hn;
	}
};

template <typename Tkey, typename Tvalue>
SkipList<Tkey, Tvalue>::~SkipList() {
	if (!heads.is_empty()) {
		Node< SkipNode<Tkey, Tvalue>* >* hn0 = heads.begin();
		SkipNode<Tkey, Tvalue>* cur = hn0 ? hn0->value : nullptr;
		while (cur != nullptr) {
			SkipNode<Tkey, Tvalue>* next = cur->next[0];
			delete cur;
			cur = next;
		}
	}
	heads.clear();
}

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
const Tvalue* SkipList<Tkey, Tvalue>::find(const Tkey& key) const {
	if (is_empty()) return nullptr;

	std::vector< SkipNode<Tkey, Tvalue>* > headPtr(lvl, nullptr);
	for (size_t i = 0; i < lvl; ++i) {
		const Node< SkipNode<Tkey, Tvalue>* >* hn = head_node_at(i);
		if (hn) headPtr[i] = hn->value;
	}

	for (int level = static_cast<int>(lvl) - 1; level >= 0; --level) {
		SkipNode<Tkey, Tvalue>* node = headPtr[level];
		while (node != nullptr && node->data.first < key) {
			node = node->next[level];
		}
		if (node != nullptr && node->data.first == key) return &node->data.second;
	}
	return nullptr;
}

template <typename Tkey, typename Tvalue>
void SkipList<Tkey, Tvalue>::push_back(const Tkey& key, const Tvalue& value) {
	size_t new_lvl = generate_lvl();
	SkipNode<Tkey, Tvalue>* new_node = new SkipNode<Tkey, Tvalue>(key, value, new_lvl);

	size_t heads_count = heads.size();
	if (heads_count < new_lvl) {
		for (size_t i = heads_count; i < new_lvl; ++i) {
			heads.push_back(nullptr);
		}
		heads_count = heads.size();
	}

	size_t use_lvl = std::max(lvl, new_lvl);
	std::vector< SkipNode<Tkey, Tvalue>* > headPtr(use_lvl, nullptr);
	for (size_t i = 0; i < use_lvl; ++i) {
		Node< SkipNode<Tkey, Tvalue>* >* hn = head_node_at_mutable(i);
		if (hn) headPtr[i] = hn->value;
	}

	std::vector< SkipNode<Tkey, Tvalue>* > update(new_lvl, nullptr);

	for (int level = static_cast<int>(new_lvl) - 1; level >= 0; --level) {
		SkipNode<Tkey, Tvalue>* prev = nullptr;
		SkipNode<Tkey, Tvalue>* cur = headPtr[level];
		while (cur != nullptr && cur->data.first < key) {
			prev = cur;
			cur = cur->next[level];
		}
		update[level] = prev;
	}

	{
		SkipNode<Tkey, Tvalue>* cur0 = update[0] ? update[0]->next[0] : headPtr[0];
		if (cur0 != nullptr && cur0->data.first == key) {
			cur0->data.second = value;
			delete new_node;
			return;
		}
	}

	for (size_t level = 0; level < new_lvl; ++level) {
		SkipNode<Tkey, Tvalue>* prev = update[level];
		if (prev == nullptr) {
			new_node->next[level] = headPtr[level];
			Node< SkipNode<Tkey, Tvalue>* >* hn = head_node_at_mutable(level);
			if (hn != nullptr) {
				hn->value = new_node;
			} else {
				heads.push_back(new_node);
			}
		} else {
			new_node->next[level] = prev->next[level];
			prev->next[level] = new_node;
		}
	}

	if (new_lvl > lvl) lvl = new_lvl;
}