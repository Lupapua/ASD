#pragma once
#include <iostream>


template <class T>
class Queue {
	T* _data;
	int _head;
	int _count;
	int _size;
public:
	Queue(): _data(nullptr), _head(0), _count(0), _size(0) {}
	Queue(int size);
	Queue(const Queue<T>& other);
	void push(const T& val);
	void pop();
	inline int head() const noexcept;
	inline bool is_full() const noexcept;
	inline bool is_empty() const noexcept;
	void clear() noexcept;
	~Queue();
};

template <class T>
Queue<T> ::Queue(int size) {
	_size = size;
	_head = 0;
	_count = 0;
	_data = new T[size];
}


template <class T>
Queue<T> ::Queue(const Queue<T>& other) {
	_size = other._size;
	_head = other._head;
	_data = new T[_size];
	_count = other._count;
	for (int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
}


template <class T>
inline bool Queue<T> :: is_full() const noexcept{
	return _size == _count;
}

template <class T>
inline bool Queue<T> ::is_empty() const noexcept {
	return _count == 0;
}

template <class T>
void Queue<T> ::push(const T& val) {
	if (is_full() != 1) {
		_count++;
		_data[(_head + _count - 1) % _size] = val;
	}
	else {
		throw std::logic_error("full data");
	}
}
 
template <class T>
void Queue<T> ::pop() {
	if (is_empty()) {
		throw std::logic_error("empty queue");
	}
	else {
		_count--;
		_head = (++_head) % _size;
	}
}

template <class T>
inline int Queue<T> ::head() const noexcept{
	return _head;
}

template <class T>
void Queue<T> ::clear() noexcept {
	_count = 0;
	_head = 0;
}

template <class T>
Queue<T>::~Queue() {
	delete[] _data;
}