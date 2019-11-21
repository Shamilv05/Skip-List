#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <atomic>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>

class Node {
public:
    int key;
    std::vector<std::shared_ptr<Node>> forward;

    Node(int, uint64_t);
};

class SkipList {
    uint64_t maximal_level;
    uint64_t number_of_levels;
    float threshold;
    std::shared_ptr<Node> header;

public:
    SkipList(uint64_t, float);
    uint64_t coin_flip(); //function to count how many time flipped coin lands of edge(creating new level for element)
    std::shared_ptr<Node> create_node(int value, uint64_t level);
    void insert_element(int key);
    void dump();
};

#endif
