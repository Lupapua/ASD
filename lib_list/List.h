#pragma once
#include <iostream>

template <class T>
struct Node
{
	T value;
	Node<T> next;
	Node(T value_, Node<T>* next_ = nullptr);
};


template <class T>
class List {
	Node <T>* _head, *_tail;
	int count;
public:
	List() : _head(nullptr), _tail(nullptr), count(0) {};
	List(const List<T>& other);
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
	Node<T>* begin();
	Node<T>* end();
	void clear() noexcept;
	~List();

	T& front();
	T& back();
	int size() const;
	void clear();
	Node<T>* begin();
	Node<T>* end();


	class Iterator {
		Node<T>* _current;
	public:
		Iterator() : _current(_head) {};
		Iterator(Node<T>* pos) : _current(pos) {};
		Iterator(const Iterator& other) : _current(other._current) {};

		Iterator& operator++() {
			if (_current != nullptr) {
				_current = _current->next;
			}
			return *this;
		}

		T& operator*() {
			return _current->value;
		}

		bool operator!=(const Iterator& other) const {
			return _current != other._current;
		}

		bool operator==(const Iterator& other) const {
			return _current == other._current;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		Iterator& operator=(const Iterator& other) {
			_current = other._current;
			return *this;
		}
	}
	typedef Iterator iterator;
};

template <class T>
Node<T> ::Node(T value_, Node<T>* next_) : value(value_), next(next_) {};


template <class T>
List<T> ::List(const List<T>& other) {
	_head = nullptr;
	_tail = nullptr;
	count = 0;
	Node<T>* current = other._head;
	while (current != nullptr) {
		push_back(current->value);
		current = current->next;
	}
}

template <class T>
void List<T> ::push_back(const T& val) {
	Node<T>* newNode = new Node<T>(val);
	if (_head == nullptr) {
		_head = newNode;
		_tail = newNode;
	}
	else {
		_tail->next = newNode;
		_tail = newNode;
	}
	count++;
}

template <class T>
void List<T> ::push_front(const T& val) {
	Node<T>* newNode = new Node<T>(val, _head);
	_head = newNode;
	if (_tail == nullptr) {
		_tail = newNode;
	}
	count++;
}

template <class T>
void List<T> ::insert(const T& val, int index) {
	if (index < 0 || index > count) {
		throw std::logic_error("incorrect index");
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
	for (int i = 0; i < index - 1; i++) {
		current = current->next;
	}
	Node<T>* newNode = new Node<T>(val, current->next);
	current->next = newNode;
	count++;
}

template <class T>
void List<T> ::insert(const T& val, Node<T>* node) {
	if (node == nullptr) {
		throw std::logic_error("null node");

	}
	if (node == _head) {
		push_front(val);
		return;
	}
	Node<T>* current = _head;
	while (current != nullptr && current->next != node) {
		current = current->next;
	}
	if (current != nullptr) {
		Node<T>* newNode = new Node<T>(val, node);
		current->next = newNode;
		count++;
	}
}

template <class T>
void List<T> ::pop_back() {
	if (_head == nullptr) {
		throw std::logic_error("list is empty");
	};
	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		Node<T>* current = _head;
		while (current->next != _tail) {
			current = current->next;
		}
		delete _tail;
		_tail = current;
		_tail->next = nullptr;
	}
	count--;
}

template <class T>
void List<T> ::pop_front() {
	if (_head == nullptr) {
		throw std::logic_error("list is empty");
	};
	Node<T>* temp = _head;
	_head = _head->next;
	delete temp;
	if (_head == nullptr) {
		_tail = nullptr;
	}
	count--;
}

template <class T>
void List<T> ::erase(int index) {
	if (index < 0 || index >= count) {
		throw std::logic_error("incorrect index");
	}
	if (index == 0) {
		pop_front();
		return;
	}
	Node<T>* current = _head;
	for (int i = 0; i < index - 1; i++) {
		current = current->next;
	}
	Node<T>* temp = current->next;
	current->next = temp->next;
	if (temp == _tail) {
		_tail = current;
	}
	delete temp;
	count--;
}

template <class T>
void List<T> ::erase(Node<T>* node) {
	if (node == nullptr || _head == nullptr) {
		throw std::logic_error("null node or empty list");
	};
	if (node == _head) {
		pop_front();
		return;
	}
	Node<T>* current = _head;
	while (current != nullptr && current->next != node) {
		current = current->next;
	}
	if (current != nullptr) {
		current->next = node->next;
		if (node == _tail) {
			_tail = current;
		}
		delete node;
		count--;
	}
}

template <class T>
bool List<T> ::is_empty() const noexcept {
	return count == 0;
}

template <class T>
Node<T>* List<T> ::find(const T& val) {
	Node<T>* current = _head;
	while (current != nullptr) {
		if (current->value == val) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

template <class T>
void List<T> ::clear() noexcept {
	Node<T>* current = _head;
	while (current != nullptr) {
		Node<T>* temp = current;
		current = current->next;
		delete temp;
	}
	_head = nullptr;
	_tail = nullptr;
	count = 0;
}

template <class T>
List<T> ::~List() {
	clear();
}

template <class T>
T& List<T> ::front() {
	return _head->value;
}

template <class T>
T& List<T> ::back() {
	return _tail->value;
}

template <class T>
int List<T> ::size() const {
	return count;
}

template <class T>
Node<T>* List<T> ::begin() {
	return _head;
}
template <class T>
Node<T>* List<T> ::end() {
	return nullptr;
}

