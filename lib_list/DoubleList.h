#pragma once
#include <iostream>

template <class T>
struct Node {
	T _value;
	Node<T>* _next;
	Node<T>* _prev;
	Node(T value, Node<T>* next = nullptr, Node<T>* prev = nullptr);
};

template <class T>
class DoubleList {
	Node<T>* _head, * _tail;
	int count;
public:
	DoubleList() : _head(nullptr), _tail(nullptr), count(0) {}
	DoubleList(const DoubleList<T>& other);
	~DoubleList();

	void push_back(const T& val);
	void push_front(const T& val);
	void insert(const T& val, int index);
	void insert(const T& val, Node<T>* node);
	void pop_back();
	void pop_front();
	void erase(int index);
	void erase(Node<T>* node);
	bool is_empty() const noexcept;
	Node<T>* find(const T& val);
	Node<T>* begin() const;
	Node<T>* end() const;
	void clear() noexcept;

	T& front();
	T& back();
	int size() const;

	class Iterator {
		Node<T>* _current;
	public:
		Iterator(Node<T>* pos = nullptr) : _current(pos) {}
		Iterator(const Iterator& other) : _current(other._current) {}

		Iterator& operator++() {
			_current = _current->_next;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		Iterator& operator--() {
			_current = _current->_prev;
			return *this;
		}
		Iterator operator--(int) {
			Iterator temp = *this;
			--(*this);
			return temp;
		}

		T& operator*() { return _current->_value; }
		T* operator->() { return &(_current->_value); }

		bool operator==(const Iterator& other) const { return _current == other._current; }
		bool operator!=(const Iterator& other) const { return _current != other._current; }

		Iterator& operator=(const Iterator& other) {
			_current = other._current;
			return *this;
		}
	};
	Iterator begin_iter() const { return Iterator(_head); }
	Iterator end_iter() const { return Iterator(nullptr); }

	Iterator rbegin_iter() const { return Iterator(_tail); }
	Iterator rend_iter() const { return Iterator(nullptr); }
};


template <class T>
Node<T>::Node(T value, Node<T>* next, Node<T>* prev)
	: _value(value), _next(next), _prev(prev) {}

template <class T>
DoubleList<T> ::DoubleList(const DoubleList<T>& other) {
	_head = nullptr;
	_tail = nullptr;
	count = 0;
	Node<T>* current = other._head;
	while (current != nullptr) {
		push_back(current->_value);
		current = current->_next;
	}
}

template <class T>
Node<T>* DoubleList<T>::begin() const{
	return _head;
}

template <class T>
Node<T>* DoubleList<T>::end() const{
	return nullptr;
}

template <class T>
DoubleList<T> :: ~DoubleList() {
	clear();
}

template <class T>
int DoubleList<T>::size() const {
	return count;
}

template <class T>
void DoubleList<T>::clear() noexcept {
	Node<T>* current = _head;
	while (current != nullptr) {
		Node<T>* next = current->_next;
		delete current;
		current = next;
	}
	_head = nullptr;
	_tail = nullptr;
	count = 0;
}

template <class T>
T& DoubleList<T>::back() {
	return _tail->_value;
}

template <class T>
T& DoubleList<T>::front() {
	return _head->_value;
}

template <class T>
bool DoubleList<T> ::is_empty() const noexcept {
	return count == 0;
}

template <class T>
void DoubleList<T> ::push_back(const T& val) {
	Node<T>* newNode = new Node<T>(val);
	if (is_empty()) {
		_head = newNode;
		_tail = newNode;
	}
	else {
		_tail->_next = newNode;
		newNode->_prev = _tail;
		_tail = newNode;
	}
	count++;
}

template <class T>
void DoubleList<T> ::push_front(const T& val) {
	Node<T>* newNode = new Node<T>(val);
	if (is_empty()) {
		_head = newNode;
		_tail = newNode;
	}
	else {
		newNode->_next = _head;
		_head->_prev = newNode;
		_head = newNode;
	}
	count++;
}

template <class T>
void DoubleList<T> ::pop_back() {
	if (is_empty()) {
		return;
	}
	Node<T>* temp = _tail;
	if (_head == _tail) {
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		_tail = _tail->_prev;
		_tail->_next = nullptr;
	}
	delete temp;
	count--;
}

template <class T>
void DoubleList<T> ::pop_front() {
	if (is_empty()) {
		return;
	}
	Node<T>* temp = _head;
	if (_head == _tail) {
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		_head = _head->_next;
		_head->_prev = nullptr;
	}
	delete temp;
	count--;
}

	
template <class T>
Node<T>* DoubleList<T> ::find(const T& val) {
	Node<T>* current = _head;
	while (current != nullptr) {
		if (current->_value == val) {
			return current;
		}
		current = current->_next;
	}
	return nullptr;
}

template <class T>
void DoubleList<T> ::erase(Node<T>* node) {
	if (node == nullptr || is_empty()) {
		return;
	}
	if (node == _head) {
		pop_front();
		return;
	}
	if (node == _tail) {
		pop_back();
		return;
	}
	Node<T>* prevNode = node->_prev;
	Node<T>* nextNode = node->_next;
	if (prevNode != nullptr) {
		prevNode->_next = nextNode;
	}
	if (nextNode != nullptr) {
		nextNode->_prev = prevNode;
	}
	delete node;
	count--;
}

template <class T>
void DoubleList<T> ::erase(int index) {
	if (index < 0 || index >= count || is_empty()) {
		return;
	}
	if (index == 0) {
		pop_front();
		return;
	}
	if (index == count - 1) {
		pop_back();
		return;
	}
	Node<T>* current = _head;
	for (int i = 0; i < index; i++) {
		current = current->_next;
	}
	erase(current);
}
template <class T>
void DoubleList<T> ::insert(const T& val, int index) {
	if (index < 0 || index > count) {
		return;
	}
	if (index == 0) {
		push_front(val);
		return;
	}
	if (index == count) {
		push_back(val);
		return;
	}
	Node<T>* current = _head;
	for (int i = 0; i < index; i++) {
		current = current->_next;
	}
	insert(val, current);
}

template <class T>
void DoubleList<T> ::insert(const T& val, Node<T>* node) {
	if (node == nullptr) {
		return;
	}
	if (node == _head) {
		push_front(val);
		return;
	}
	Node<T>* newNode = new Node<T>(val);
	Node<T>* prevNode = node->_prev;
	newNode->_next = node;
	newNode->_prev = prevNode;
	if (prevNode != nullptr) {
		prevNode->_next = newNode;
	}
	node->_prev = newNode;
	count++;
}