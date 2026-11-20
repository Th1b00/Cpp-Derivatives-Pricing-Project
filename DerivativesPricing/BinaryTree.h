#pragma once

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

template <class T>
class BinaryTree {
private:
    int _depth;
    std::vector<std::vector<T>> _tree;

public:
    explicit BinaryTree(int depth = 0) : _depth(0) { setDepth(depth); }

    void setDepth(int depth) {
        if (depth < 0) throw std::invalid_argument("Tree depth must be nonnegative");
        _depth = depth;
        _tree.resize(static_cast<std::size_t>(depth) + 1);
        for (int n = 0; n <= depth; ++n)
            _tree[static_cast<std::size_t>(n)].resize(static_cast<std::size_t>(n) + 1);
    }

    void setNode(int n, int i, T value) {
        if (n < 0 || n > _depth || i < 0 || i > n)
            throw std::out_of_range("BinaryTree node index out of range");
        _tree[static_cast<std::size_t>(n)][static_cast<std::size_t>(i)] = value;
    }

    T getNode(int n, int i) const {
        if (n < 0 || n > _depth || i < 0 || i > n)
            throw std::out_of_range("BinaryTree node index out of range");
        return _tree[static_cast<std::size_t>(n)][static_cast<std::size_t>(i)];
    }

    void display() const {
        for (int n = 0; n <= _depth; ++n) {
            for (int i = 0; i <= n; ++i) {
                if (i) std::cout << ' ';
                std::cout << _tree[static_cast<std::size_t>(n)][static_cast<std::size_t>(i)];
            }
            std::cout << '\n';
        }
        std::cout << '\n';

        for (int n = 0; n <= _depth; ++n) {
            std::string indent(static_cast<std::size_t>(2 * (_depth - n)), ' ');

            std::cout << indent;
            for (int i = 0; i <= n; ++i)
                std::cout << std::setw(3) << _tree[static_cast<std::size_t>(n)][static_cast<std::size_t>(i)] << ' ';
            std::cout << '\n';

            if (n < _depth) {
                std::cout << indent;
                for (int i = 0; i <= n; ++i) std::cout << " / \\";
                std::cout << '\n';
            }
        }
        std::cout << '\n';
    }
};