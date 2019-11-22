#ifndef NODE_NODE_H
#define NODE_NODE_H

#include "skiplist.hpp"

extern int max_level;

template<class T> struct Node {
    T value;
    int key;
    int top_level;

    std::vector<AtomicMarkableReference<Node<T>>> next;

    Node() {
        value = nullptr;
        key = 0;
        top_level = max_level;
        next = std::vector<AtomicMarkableReference<Node<T>>>(max_level + 1);
    }

    Node(int n_key, T n_value, int height = max_level) {
        key = n_key;
        value = n_value;
        top_level = height;
        next = std::vector<AtomicMarkableReference<Node<T>>>(max_level + 1);
    }
};

#endif
