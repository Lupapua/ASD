#pragma once
#include <iostream>
#include <queue>

template<typename Tkey, typename Tvalue>
struct Node {
    std::pair<Tkey, Tvalue> data;
    Node* left;
    Node* right;
public:
    Node(const Tkey& key, const Tvalue& value)
        : data(key, value), left(nullptr), right(nullptr) {
    }
    Node() : data(), left(nullptr), right(nullptr) {}
};

template<typename Tkey, typename Tvalue>
class Tree {
private:
    Node<Tkey, Tvalue>* _root;

    // обходы принимают ostream& для гибкого вывода
    void lcr_rec(Node<Tkey, Tvalue>* node, std::ostream& out) const {
        if (node == nullptr) return;
        lcr_rec(node->left, out);
        out << "(" << node->data.first << ":" << node->data.second << ") ";
        lcr_rec(node->right, out);
    }
    void lrc_rec(Node<Tkey, Tvalue>* node, std::ostream& out) const {
        if (node == nullptr) return;
        lrc_rec(node->left, out);
        lrc_rec(node->right, out);
        out << "(" << node->data.first << ":" << node->data.second << ") ";
    }
    void clr_rec(Node<Tkey, Tvalue>* node, std::ostream& out) const {
        if (node == nullptr) return;
        out << "(" << node->data.first << ":" << node->data.second << ") ";
        clr_rec(node->left, out);
        clr_rec(node->right, out);
    }
    void width_rec(std::ostream& out) const {
        if (is_empty()) {
            out << "WIDTH: Tree is empty" << std::endl;
            return;
        }
        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);
        int level = 0;
        while (!q.empty()) {
            int levelSize = static_cast<int>(q.size());
            out << "Level " << level << ": ";
            for (int i = 0; i < levelSize; i++) {
                Node<Tkey, Tvalue>* node = q.front();
                q.pop();
                out << "(" << node->data.first << ":" << node->data.second << ") ";
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            out << std::endl;
            level++;
        }
    }

    void deleteTree(Node<Tkey, Tvalue>* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    Tree() : _root(nullptr) {}
    ~Tree() { deleteTree(_root); }

    // Вставка: level-order. Если ключ найден — обновляем значение.
    void insert(const Tkey& key, const Tvalue& value) {
        if (_root == nullptr) {
            _root = new Node<Tkey, Tvalue>(key, value);
            return;
        }
        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);
        while (!q.empty()) {
            Node<Tkey, Tvalue>* node = q.front();
            q.pop();
            if (node->data.first == key) {
                node->data.second = value;
                return;
            }
            if (!node->left) {
                node->left = new Node<Tkey, Tvalue>(key, value);
                return;
            } else q.push(node->left);

            if (!node->right) {
                node->right = new Node<Tkey, Tvalue>(key, value);
                return;
            } else q.push(node->right);
        }
    }

    // Поиск ключа обходом (BFS). Возвращает указатель на значение или nullptr.
    const Tvalue* find(const Tkey& key) const {
        if (_root == nullptr) return nullptr;
        std::queue<Node<Tkey, Tvalue>*> q;
        q.push(_root);
        while (!q.empty()) {
            Node<Tkey, Tvalue>* node = q.front(); q.pop();
            if (node->data.first == key) return &node->data.second;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return nullptr;
    }

    // Удаление: найти узел с ключом и последний узел уровня; заменить и удалить последний.
    void remove(const Tkey& key) {
        if (_root == nullptr) return;

        Node<Tkey, Tvalue>* node_to_remove = nullptr;
        Node<Tkey, Tvalue>* last = nullptr;
        Node<Tkey, Tvalue>* parent_of_last = nullptr;

        std::queue<std::pair<Node<Tkey, Tvalue>*, Node<Tkey, Tvalue>*>> q; // pair(node, parent)
        q.push({ _root, nullptr });

        while (!q.empty()) {
            auto pr = q.front(); q.pop();
            Node<Tkey, Tvalue>* node = pr.first;
            Node<Tkey, Tvalue>* parent = pr.second;

            // track last and its parent
            last = node;
            parent_of_last = parent;

            if (node->data.first == key) node_to_remove = node;

            if (node->left) q.push({ node->left, node });
            if (node->right) q.push({ node->right, node });
        }

        if (node_to_remove == nullptr) {
            // ключ не найден — ничего не делаем
            return;
        }

        if (last == nullptr) return; // на всякий

        // Если удаляем именно последний узел
        if (node_to_remove == last) {
            if (parent_of_last == nullptr) {
                // удаляем корень — дерево становится пустым
                delete _root;
                _root = nullptr;
            } else {
                if (parent_of_last->left == last) parent_of_last->left = nullptr;
                else if (parent_of_last->right == last) parent_of_last->right = nullptr;
                delete last;
            }
            return;
        }

        // копируем данные последнего в удаляемый и удаляем последний
        node_to_remove->data = last->data;
        if (parent_of_last == nullptr) {
            // последний — корень (это возможно только если дерево состояло из одного узла, но мы уже обрабатывали)
            delete last;
            _root = nullptr;
            return;
        } else {
            if (parent_of_last->left == last) parent_of_last->left = nullptr;
            else if (parent_of_last->right == last) parent_of_last->right = nullptr;
            delete last;
        }
    }

    bool is_empty() const { return _root == nullptr; }

    // Перегруженные методы — для вывода в std::cout
    void lcr() const {
        lcr(std::cout);
    }
    void lrc() const {
        lrc(std::cout);
    }
    void clr() const {
        clr(std::cout);
    }
    void width() const {
        width(std::cout);
    }

    // Методы с явным потоком вывода
    void lcr(std::ostream& out) const {
        out << "LCR: ";
        lcr_rec(_root, out);
        out << std::endl;
    }
    void lrc(std::ostream& out) const {
        out << "LRC: ";
        lrc_rec(_root, out);
        out << std::endl;
    }
    void clr(std::ostream& out) const {
        out << "CLR: ";
        clr_rec(_root, out);
        out << std::endl;
    }
    void width(std::ostream& out) const {
        out << "WIDTH: ";
        width_rec(out);
    }
};