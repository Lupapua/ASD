#pragma once
#include <iostream>
using namespace std;
#define STEP_CAPACITY 15

template <class T> class TVector;
template <class T> ostream& operator<<(ostream& out, const TVector<T>& dmass);

inline int calc_capacity(int n) {
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
    if (n < 0) {
        throw logic_error("n < 0");
    }

    // если нужно увеличить буфер Ч вычисл€ем Ємкость по требуемому n (не по старому _size)
    if (static_cast<size_t>(n) > _capacity) {
        _capacity = calc_capacity(n);
        T* new_data = new T[_capacity];
        // копируем только существующие элементы (по _size)
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = _data[i];
        }
        if (_data != nullptr) {
            delete[] _data;
        }
        _data = new_data;
    }
    _size = static_cast<size_t>(n);
}


template <class T>
std::ostream& operator<<(std::ostream& out, const TVector<T>& dmass) {
    out << "( ";
    for (size_t i = 0; i < static_cast<size_t>(dmass.size()); i++) {
        out << dmass[i] << " ";
    }
    out << ")";
    return out;
}

template <class T>
TVector<T>::TVector(std::initializer_list<T> data) {
    _size = data.size();
    _capacity = calc_capacity(static_cast<int>(_size));
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = *(data.begin() + i);
    }

};

template <class T>
TVector<T>::TVector(const TVector& other) : _size(other._size), _capacity(calc_capacity(static_cast<int>(other._size))) {
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
};

template <class T>
TVector<T>::TVector(const T* arr, size_t n) : _size(n), _capacity(calc_capacity(static_cast<int>(n))) {
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = arr[i];
    }
};

template <class T>
TVector<T>::TVector(int n){
    if (n >= 0) {
        _size = static_cast<size_t>(n);
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
    return static_cast<int>(_size);
}

template <class T>
inline int TVector<T>::capacity() const noexcept {
    return static_cast<int>(_capacity);
}

template <class T>
void TVector<T>::push_back(const T& number) {
    update_capacity(static_cast<int>(_size) + 1);
    _data[_size - 1] = number;
}

template <class T>
void TVector<T>::push_front(const T& number) {
    update_capacity(static_cast<int>(_size) + 1);
    for (size_t i = 0; i < _size - 1; ++i) {
        _data[_size - i - 1] = _data[_size - i - 2];
    }
    _data[0] = number;
}

template <class T>
int TVector<T>::find_first(T number) {
    if (_data == nullptr || _size == 0) {
        throw logic_error("not finded");
    }

    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == number) {
            return static_cast<int>(i) + 1;
        }
    }
    throw logic_error("not finded");
}

template <class T>
int TVector<T>::find_last(T number) {
    if (_data == nullptr || _size == 0) {
        throw logic_error("not finded");
    }

    int i = static_cast<int>(_size) - 1;
    while (i >= 0 && _data[i] != number) {
        --i;
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
    if (pos >= 1 && pos <= static_cast<int>(_size) && (pos + count) <= static_cast<int>(_size)) {
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
    if (pos >= 1 && pos <= static_cast<int>(_size)) {
        for (int i = pos; i < static_cast<int>(_size); i++) {
            _data[i - 1] = _data[i];
        }
        update_capacity(static_cast<int>(_size) - 1);
    }
    else {
        throw logic_error("incorrect position");
    }
}

template <class T>
void TVector<T>::pop_back() {
    pop(static_cast<int>(_size));
}

template <class T>
void TVector<T>::pop_front() {
    pop(1);
}

