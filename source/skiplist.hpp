#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <atomic>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <mutex>

class Node {
    std::mutex node_m;
public:
    int key;
    std::vector<std::shared_ptr<Node>> forward;

    Node(int, uint64_t);
    void lock();
    void unlock();
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
    void search_element(int value);
    void delete_element(int value);
    void dump();
};

#endif
