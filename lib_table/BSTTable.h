#pragma once
#include <iostream>
#include <utility>
#include <stdexcept>
#include "ITable.h"
#include "../lib_bstree/BSTree.h"

template <typename Tkey, typename Tvalue>
class BSTreeTable : public ITable<Tkey, Tvalue> {
private:
	BSTree<Tkey, Tvalue> _tree;

public:
	BSTreeTable() {}
	~BSTreeTable() {}

	void insert(const Tkey& key, const Tvalue& val) override {
		try {
			_tree.insert(key, val);
		}
		catch (const std::logic_error& e) {
			if (std::string(e.what()) == "key already exists") {
				_tree.erase(key);
				_tree.insert(key, val);
			}
			else {
				throw;
			}
		}
	}

	Tvalue find(const Tkey& key) const override {
		if(!consist(key)) {
			throw std::logic_error("key not found");
		}
		return const_cast<Tvalue&>(_tree.find(key));
	}

	void erase(const Tkey& key) override {
		_tree.erase(key);
	}

	std::ostream& print(std::ostream& out) const noexcept override {
		out << "{ " << _tree.to_string_sorted() << "}";
		return out;
	}

	bool is_empty() const noexcept override {
		return _tree.is_empty();
	}

	bool consist(const Tkey& key) const noexcept override {
		try {
			_tree.find(key);
			return true;
		}
		catch (const std::logic_error&) {
			return false;
		}
	}
};