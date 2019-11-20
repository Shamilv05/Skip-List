#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <atomic>
#include <cstring>
#include <cstdlib>

class Node {
public:
    int key;
    Node **forward;

    Node(int, uint64_t);
};

class SkipList {
    uint64_t maximal_level;
    uint64_t current_level;
    float fraction_of_nodes;
    Node *header;

public:
    SkipList(uint64_t, float);
    int randomLevel(); //function to count how many time flipped coin lands of edge(creating new level for element)
};

#endif
