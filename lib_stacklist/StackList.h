#pragma once
#include <iostream>
#include "../lib_list/List.h"

template <class T>
class StackList {
	List _data;
public:
	void push(const T& val);
	T& top();
	void pop();
	inline bool is_empty() const noexcept;
	void clear() noexcept;
};

template <class T>
void StackList<T> ::push(const T& val) {
	_top++;
	_data.push_back(val);
}

template <class T>
T& StackList<T> ::top() {
	if (_data.is_empty()) {
		throw std::logic_error("Stack is empty");
	}
	return _data.back();
}

template <class T>
inline bool StackList<T> ::is_empty() const noexcept {
	return _data.is_empty();
}



template <class T>
void StackList<T> ::pop() {
	if (_data.is_empty()) {
		throw std::logic_error("Stack is empty");
	}
	_top--;
	_data.pop_back();
}

template <class T>
void StackList<T> ::clear() noexcept {
	_data.clear();
}
