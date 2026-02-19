#pragma once
#include <iostream>
using namespace std;
#define STEP_CAPACITY 15

template <class T> class TVector;
template <class T> ostream& operator<<(ostream& out, const TVector<T>& dmass);

int calc_capacity(int n) {
    return (n + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;
}

template <class T>
class TVector {
protected:
    T* _data;
    size_t _capacity;
    size_t _size;

public:
    TVector() : _data(nullptr), _size(0), _capacity(0) {}
    TVector(const TVector& other);
    TVector& operator=(const TVector& other);
    TVector(const T* arr, size_t n);
    TVector(int n);
    TVector(std::initializer_list<T> data);
    ~TVector() { delete[] _data; }

    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;

    int size() const noexcept;
    int capacity() const noexcept;

    void push_back(const T& number);
    void push_front(const T& number);
    void update_capacity(int n);

    int find_first(T number);
    int find_last(T number);

    void erase(int pos, int count);
    void pop(int pos);
    void pop_back();
    void pop_front();


    class Iterator {
        T* _ptr;
    public:
        Iterator(T* ptr = nullptr) : _ptr(ptr) {}

        Iterator& operator++() {
            ++_ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        T& operator*() const {
            return *_ptr;
        }

        bool operator!=(const Iterator& other) const {
            return _ptr != other._ptr;
        }

        bool operator==(const Iterator& other) const {
            return _ptr == other._ptr;
        }

        Iterator& operator=(const Iterator& other) {
            _ptr = other._ptr;
            return *this;
        }

    };

    Iterator begin() const { return Iterator(_data); }
    Iterator end() const { return Iterator(_data + _size); }

    friend std::ostream& operator<< <>(std::ostream& out, const TVector<T>& dmass);
};

template <class T>
TVector<T>& TVector<T>::operator=(const TVector& other) {
    if (this != &other) {
        if (_data != nullptr) {
            delete[] _data;
        }

        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];

        for (size_t i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template <class T>
void TVector<T>::update_capacity(int n) {
    if (n >= 0) {
       
        if (n >= _capacity) {
            _capacity = calc_capacity(_size);
            T* new_data = new T[_capacity];
            for (int i = 0; i < _size; i++) {
                new_data[i] = _data[i];
            }
            if (_data != nullptr) {
                delete[] _data;
            }
            _data = new_data;
        }
        _size = n;
    }
    else {
        throw logic_error("n < 0");
    }
}


template <class T>
std::ostream& operator<<(std::ostream& out, const TVector<T>& dmass) {
    out << "( ";
    for (size_t i = 0; i < dmass.size(); i++) {
        out << dmass[i] << " ";
    }
    out << ")";
    return out;
}

template <class T>
TVector<T>::TVector(std::initializer_list<T> data) {
    _size = data.size();
    _capacity = calc_capacity(_size);
    _data = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = *(data.begin() + i);
    }

};

template <class T>
TVector<T>::TVector(const TVector& other) : _size(other._size), _capacity(calc_capacity(other._size)) {
    _data = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
};

template <class T>
TVector<T>::TVector(const T* arr, size_t n) : _size(n), _capacity(calc_capacity(n)) {
    _data = new T[_capacity];
    for (int i = 0; i < _size; ++i) {
        _data[i] = arr[i];
    }
};

template <class T>
TVector<T>::TVector(int n){
    if (n >= 0) {
        _size = n;
        _capacity = calc_capacity(n);
        _data = new T[_capacity];
    }
    else {
        throw logic_error("n < 0");
    }
};

template <class T>
inline T& TVector<T>::operator[](size_t index) noexcept {
    return _data[index];
}

template <class T>
inline const T& TVector<T>::operator[](size_t index) const noexcept {
    return _data[index];
}

template <class T>
inline int TVector<T>::size() const noexcept {
    return _size;
}

template <class T>
inline int TVector<T>::capacity() const noexcept {
    return _capacity;
}

template <class T>
void TVector<T>::push_back(const T& number) {
    update_capacity(_size + 1);
    _data[_size - 1] = number;
}

template <class T>
void TVector<T>::push_front(const T& number) {
    update_capacity(_size + 1);
    for (int i = 0; i < _size; i++) {
        _data[_size - 1 - i] = _data[_size - 2 - i];
    }
    _data[0] = number;
}

template <class T>
int TVector<T>::find_first(T number) {
    if (_data == nullptr || _size == 0) {
        throw logic_error("not finded");
    }

    for (int i = 0; i < _size; i++) {
        if (_data[i] == number) {
            return i + 1;
        }
    }
    throw logic_error("not finded");
}

template <class T>
int TVector<T>::find_last(T number) {
    int i = _size - 1;

    if (_data == nullptr || _size == 0) {
        throw logic_error("not finded");
    }

    while (i >= 0 && _data[i] != number)
    {
        i--;
    }
    if (i >= 0) {
        return i + 1;
    }
    else {
        throw logic_error("not finded");
    }
}


template <class T>
void TVector<T>::erase(int pos, int count) {
    if (pos >= 1 && pos <= _size && (pos+count) <= _size) {
        for (int j = 0; j < count; j++) {
            pop(pos);
        }
    }
    else {
        throw logic_error("incorrect pos or count or both");
    }
    
}

template <class T>
void TVector<T>::pop(int pos) {
    if (pos >= 1 && pos <= _size) {
        for (int i = pos; i < _size; i++) {
            _data[i - 1] = _data[i];
        }
        update_capacity(_size - 1);
    }
    else {
        throw logic_error("incorrect position");
    }
}

template <class T>
void TVector<T>::pop_back() {
    pop(_size);
}

template <class T>
void TVector<T>::pop_front() {
    pop(1);
}

