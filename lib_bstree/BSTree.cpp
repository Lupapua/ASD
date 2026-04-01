#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <stdexcept>
#include <sstream>

template <typename TKey, typename TValue>
struct Node {
	std::pair<TKey, TValue> data;
	Node* left;
	Node* right;

	Node(const TKey& key, const TValue& val, Node* l = nullptr, Node* r = nullptr)
		: data(std::pair<TKey, TValue>(key, val)), left(l), right(r) {
	}
};

template <typename TKey, typename TValue>
class BSTree {
private:
	Node<TKey, TValue>* _root;
	Node<TKey, TValue>* find_pos(const TKey& key) const noexcept;

	static void deletetree(Node<TKey, TValue>* node) {
		if (!node) return;
		deletetree(node->left);
		deletetree(node->right);
		delete node;
	}
	void to_string_pre(Node<TKey, TValue>* node, std::ostringstream& os) const noexcept {
		if (!node) return;
		os << node->data.first << ":" << node->data.second << " ";
		to_string_pre(node->left, os);
		to_string_pre(node->right, os);
	}
	void to_string_in(Node<TKey, TValue>* node, std::ostringstream& os) const noexcept {
		if (!node) return;
		to_string_in(node->left, os);
		os << node->data.first << ":" << node->data.second << " ";
		to_string_in(node->right, os);
	}

public:
	BSTree() : _root(nullptr) {}
	void insert(const TKey& key, const TValue& value);
	const TValue& find(const TKey& key) const;
	void erase(const TKey& key);
	bool is_empty() const noexcept;
	std::string to_string() const noexcept;
	std::string to_string_sorted() const noexcept;
	~BSTree();
};

template <typename TKey, typename TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept {
	return _root == nullptr;
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_pos(const TKey& key) const noexcept {
	Node<TKey, TValue>* cur = _root;
	Node<TKey, TValue>* parent = nullptr;
	while (cur) {
		if (cur->data.first == key)
			return cur;
		parent = cur;
		if (key < cur->data.first)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return parent;
}

template <typename TKey, typename TValue>
const TValue& BSTree<TKey, TValue>::find(const TKey& key) const {
	Node<TKey, TValue>* found = find_pos(key);
	if (found && found->data.first == key)
		return found->data.second;
	throw std::logic_error("key not found");
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
	if (is_empty()) {
		_root = new Node<TKey, TValue>(key, val);
		return;
	}
	Node<TKey, TValue>* pos = find_pos(key);
	if (pos && pos->data.first == key)
		throw std::logic_error("key already exists");
	Node<TKey, TValue>* node = new Node<TKey, TValue>(key, val);
	if (key < pos->data.first)
		pos->left = node;
	else
		pos->right = node;
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
	if (is_empty()) throw std::logic_error("key not found");

	Node<TKey, TValue>* parent = nullptr;
	Node<TKey, TValue>* cur = _root;
	while (cur && cur->data.first != key) {
		parent = cur;
		if (key < cur->data.first) cur = cur->left;
		else cur = cur->right;
	}
	if (!cur) throw std::logic_error("key not found");

	if (cur->left && cur->right) {
		Node<TKey, TValue>* succ_parent = cur;
		Node<TKey, TValue>* succ = cur->right;
		while (succ->left) {
			succ_parent = succ;
			succ = succ->left;
		}
		cur->data = succ->data;
		parent = succ_parent;
		cur = succ;
	}

	Node<TKey, TValue>* child = (cur->left) ? cur->left : cur->right;

	if (parent == nullptr) {
		_root = child;
	}
	else if (parent->left == cur) {
		parent->left = child;
	}
	else {
		parent->right = child;
	}
	delete cur;
}

template <typename TKey, typename TValue>
std::string BSTree<TKey, TValue>::to_string() const noexcept {
	std::ostringstream os;
	to_string_pre(_root, os);
	return os.str();
}

template <typename TKey, typename TValue>
std::string BSTree<TKey, TValue>::to_string_sorted() const noexcept {
	std::ostringstream os;
	to_string_in(_root, os);
	return os.str();
}

template <typename TKey, typename TValue>
BSTree<TKey, TValue>::~BSTree() {
	deletetree(_root);
	_root = nullptr;
}