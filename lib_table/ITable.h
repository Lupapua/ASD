#pragma once
#include <iostream>
#include <utility>
#include <stdexcept>
#include "../lib_tvector/TVector.h"

template <typename Tkey, typename Tvalue>
class ITable {
public:
    ~ITable() {};
    virtual void insert(const Tkey& key, const Tvalue& val) = 0;
    virtual Tvalue find(const Tkey& key) const = 0;
    virtual void erase(const Tkey& key) = 0;
    virtual std::ostream& print(std::ostream& out) const noexcept = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual bool consist(const Tkey& key) const noexcept = 0;

};

template <typename Tkey, typename Tvalue>
class UnsortedTableOnVec : public ITable<Tkey, Tvalue> {
private:
    TVector<std::pair <Tkey, Tvalue>> _rows;

public:
    ~UnsortedTableOnVec() {};
    UnsortedTableOnVec() {};
    bool is_empty() const noexcept;
    void insert(const Tkey& key, const Tvalue& val) override;
    Tvalue find(const Tkey& key) const override;
    void erase(const Tkey& key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool consist(const Tkey& key) const noexcept override;
};

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey, Tvalue> ::is_empty() const noexcept {
    return _rows.size() == 0;
}

template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue> ::insert(const Tkey& key, const Tvalue& val) {
    _rows.push_back({ key, val });
}

template <typename Tkey, typename Tvalue>
Tvalue UnsortedTableOnVec<Tkey, Tvalue> ::find(const Tkey& key) const {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            return _rows[i].second;
        }
    }
    throw std::logic_error("didn't find key");
}

template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::erase(const Tkey& key) {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            _rows.pop(i + 1);
            return;
        }
    }
    throw std::logic_error("can't erase: key not found");
}

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey, Tvalue>::consist(const Tkey& key) const noexcept {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            return true;
        }
    }
    return false;
}

template <typename Tkey, typename Tvalue>
std::ostream& UnsortedTableOnVec<Tkey, Tvalue>::print(std::ostream& out) const noexcept {
    out << "{ ";
    for (int i = 0; i < _rows.size(); ++i) {
        out << "(" << _rows[i].first << ", " << _rows[i].second << ") ";
    }
    out << "}";
    return out;
}

template <typename Tkey, typename Tvalue>
class SortedTableOnVec : public ITable<Tkey, Tvalue> {
private:
    TVector<std::pair<Tkey, Tvalue>> _rows;

    std::pair<bool, int> binary_find(const Tkey& key) const {
        if (_rows.size() == 0) return { false, 0 };
        int lo = 0;
        int hi = _rows.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (_rows[mid].first == key) return { true, mid };
            if (_rows[mid].first < key) lo = mid + 1;
            else hi = mid - 1;
        }
        return { false, lo };
    }

public:
    SortedTableOnVec() {}
    ~SortedTableOnVec() {}

    bool is_empty() const noexcept override {
        return _rows.size() == 0;
    }

    void insert(const Tkey& key, const Tvalue& val) override {
        if (_rows.size() == 0) {
            _rows.push_back({ key, val });
            return;
        }
        auto res = binary_find(key);
        if (res.first) {
            _rows[res.second].second = val;
            return;
        }
        int pos = res.second;

        int old_size = _rows.size();
        _rows.update_capacity(old_size + 1);

        for (int i = old_size; i > pos; --i) {
            _rows[i] = _rows[i - 1];
        }
        _rows[pos] = std::pair<Tkey, Tvalue>(key, val);
    }

    Tvalue find(const Tkey& key) const override {
        if (_rows.size() == 0) throw std::logic_error("didn't find key");
        auto res = binary_find(key);
        if (res.first) return _rows[res.second].second;
        throw std::logic_error("didn't find key");
    }

    void erase(const Tkey& key) override {
        if (_rows.size() == 0) throw std::logic_error("can't erase: empty");
        auto res = binary_find(key);
        if (!res.first) throw std::logic_error("can't erase: key not found");
        _rows.pop(res.second + 1);
    }

    bool consist(const Tkey& key) const noexcept override {
        if (_rows.size() == 0) return false;
        auto res = binary_find(key);
        return res.first;
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        out << "{ ";
        for (int i = 0; i < _rows.size(); ++i) {
            out << "(" << _rows[i].first << ", " << _rows[i].second << ") ";
        }
        out << "}";
        return out;
    }
};
