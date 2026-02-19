#pragma once
#include <iostream>
#include "../lib_tvector/TVector.h"

template <typename Tkey, typename Tvalue>
class ITable {
public:
	~ITable() {};
	virtual void insert(const Tkey& key, const Tvalue& val) = 0;
	virtual Tvalue find(const Tkey& key) const = 0;
	virtual void erase(const Tkey& key) = 0;
	virtual ostream& print(ostream& out) const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist (const Tkey& key) const noexcept = 0;
};

template <typename Tkey, typename Tvalue>
class UnsortedTableOnVec : public ITable<Tkey, Tvalue> {
private:
	Tvector<std::pair <Tkey, Tvalue>> _rows;
	
public:
	~UnsortedTableOnVec() {};
	UnsortedTableOnVec() {};
	bool is_empty() const noexcept;
	void insert(const Tkey& key, const Tvalue& val);
	Tvalue find(const Tkey& key) const;
	void erase(const Tkey& key);
	ostream& print(ostream& out) const noexcept;
	bool is_empty() const noexcept;
	bool consist(const Tkey& key) const noexcept;
};

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey,Tvalue> :: is_empty() const noexcept {
	return _rows.size() == 0;
}

template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue> :: insert(const Tkey& key, const Tvalue& val) {
	_rows.pushback({ key, val });
}

template <typename Tkey, typename Tvalue>
Tvalue UnsortedTableOnVec<Tkey, Tvalue> ::find(const Tkey& key) const {
	for (i = 0; i < _rows.size(); i++) {
		if (_rows[i].first == key) {
			return _rows[i].second
		}
	}
	throw logic_error("didnt find key");
};

template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::erase(const Tkey& key) {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            _rows.pop(i + 1);
            return;
        }
    }
    throw std::logic_error("can't erase: key not found");
}

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey, Tvalue>::consist(const Tkey& key) const noexcept {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            return true;
        }
    }
    return false;
}

template <typename Tkey, typename Tvalue>
std::ostream& UnsortedTableOnVec<Tkey, Tvalue>::print(std::ostream& out) const noexcept {
    out << "{ ";
    for (int i = 0; i < _rows.size(); i++) {
        out << "(" << _rows[i].first << ", " << _rows[i].second << ") ";
    }
    out << "}";
    return out;
}
