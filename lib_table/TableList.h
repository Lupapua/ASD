#pragma once
#include <iostream>
#include <utility>
#include <stdexcept>
#include "../lib_table/ITable.h"
#include "../lib_list/List.h"

template<typename Tkey, typename Tvalue>
class UnsortedTableOnList : public ITable<Tkey, Tvalue> {
private:
    List<std::pair<Tkey, Tvalue>> _list;
public:
    UnsortedTableOnList() {}
    ~UnsortedTableOnList() {}

    bool consist(const Tkey& key) const noexcept override {
        for (auto it = _list.begin_iter(); it != _list.end_iter(); ++it) {
            if ((*it).first == key) { return true; }
        }
        return false;
    }

    void insert(const Tkey& key, const Tvalue& value) override {
        if (consist(key)) { throw std::logic_error("Key already exists"); }
        _list.push_back(std::make_pair(key, value));
    }

    void replace(const Tkey& key, const Tvalue& value) {
        for (auto it = _list.begin_iter(); it != _list.end_iter(); ++it) {
            if ((*it).first == key) {
                (*it).second = value;
                return;
            }
        }
        insert(key, value);
    }

    Tvalue find(const Tkey& key) const override {
        for (auto it = _list.begin_iter(); it != _list.end_iter(); ++it) {
            if ((*it).first == key) {
                return (*it).second;
            }
        }
        throw std::logic_error("Key not found");
    }

    bool is_empty() const noexcept override {
        return _list.is_empty();
    }

    void erase(const Tkey& key) override {
        size_t pos = 0;
        for (auto it = _list.begin_iter(); it != _list.end_iter(); ++it, ++pos) {
            if ((*it).first == key) {
                _list.erase(static_cast<int>(pos));
                return;
            }
        }
        throw std::logic_error("can't erase: key not found");
    }

    std::ostream& print(std::ostream& os) const noexcept override {
        for (auto it = _list.begin_iter(); it != _list.end_iter(); ++it) {
            os << "|" << (*it).first << "|" << (*it).second << "|\n";
        }
        return os;
    }
};