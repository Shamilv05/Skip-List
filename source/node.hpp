#ifndef NODE_NODE_H
#define NODE_NODE_H

#include "skiplist.hpp"

int max_level = 20;

template<class T> struct Node {
    T value;
    int key;
    int top_level;

    std::vector<AtomicMarkableReference<Node<T>>> next;

    Node() {
        key = 0;
        top_level = max_level;
        next = std::vector<AtomicMarkableReference<Node<T>>>(max_level + 1);
    }

    Node(int n_key, T n_value, int height = max_level) {
        this->key = n_key;
        this->value = n_value;
        top_level = height;
        next = std::vector<AtomicMarkableReference<Node<T>>>(height + 1);
    }
};

#endif
