#pragma once
#include "ITable.h"
#include "../lib_tree/Tree.h"
#include <iostream>
#include <stdexcept>

template<typename Tkey, typename Tvalue>
class UnsortedTableOnTree : public ITable<Tkey, Tvalue> {
private:
    Tree<Tkey, Tvalue> _tree;
public:
    UnsortedTableOnTree() {}
    ~UnsortedTableOnTree() {}

    void insert(const Tkey& key, const Tvalue& val) override {
        _tree.insert(key, val);
    }

    Tvalue find(const Tkey& key) const override {
        const Tvalue* p = _tree.find(key);
        if (p == nullptr) throw std::logic_error("didn't find key");
        return *p;
    }

    void erase(const Tkey& key) override {
        if (_tree.find(key) == nullptr) throw std::logic_error("can't erase: key not found");
        _tree.remove(key);
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        _tree.lcr(out);
        return out;
    }

    bool is_empty() const noexcept override {
        return _tree.is_empty();
    }

    bool consist(const Tkey& key) const noexcept override {
        return _tree.find(key) != nullptr;
    }
};

