#pragma once
#include <iostream>


template <class T>
class Stack {
	T* _data;
	int _size;
	int _top;
public:
	Stack(): _data(nullptr), _size(0), _top(-1){}
	Stack(int size);
	void push(const T& val);
	inline int top() const noexcept;
	void pop();
	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
	void clear() noexcept;
	void print();
	~Stack() {
		delete[] _data;
	}
};

template <class T>
void Stack<T> ::print(){
	for (int i = 0; i <= _top; i++) {
		std::cout << _data[i];
	}
}

template <class T>
inline int Stack<T> :: top() const noexcept {
	return _top;
}

template <class T>
Stack<T> ::Stack(int size){
	_size = size;
	_top = -1;
	_data = new T[_size];
}

template <class T>
void Stack<T> ::push(const T& val) {
	if (is_full()) {
		throw std::logic_error("Stack is full");
	}
	_top++;
	_data[_top] = val;
}

template <class T>
inline bool Stack<T> ::is_empty() const noexcept {
	return _top == -1;
}

template <class T>
inline bool Stack<T> ::is_full() const noexcept {
	return _top == _size -1;
}

template <class T>
void Stack<T> ::pop() {
	if (is_empty()) {
		throw std::logic_error("Stack is empty");
	}
	else {
		_top -= 1;
	}
}

template <class T>
void Stack<T>::clear() noexcept {
	_top = -1;
}