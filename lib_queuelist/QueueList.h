#pragma once
#include <iostream>
#include "../lib_list/List.h"

template <class T>
class QueueList {
	List _data;
public:
	void push(const T& val);
	void pop();
	T& head();
	inline bool is_empty() const noexcept;
	void clear() noexcept;
};

template <class T>
void QueueList<T> ::push(const T& val) {
	_data.push_back(val);
}

template <class T>
void QueueList<T> ::pop() {
	if (_data.is_empty()) {
		throw std::logic_error("Queue is empty");
	}
	_data.pop_front();
}

template <class T>
T& QueueList<T> ::head() {
	if (_data.is_empty()) {
		throw std::logic_error("Queue is empty");
	}
	return _data.front();
}

template <class T>
inline bool QueueList<T> ::is_empty() const noexcept {
	return _data.is_empty();
}

template <class T>
void QueueList<T> ::clear() noexcept {
	_data.clear();
}

