#include "skiplist.hpp"

Node::Node(int key, uint64_t level) {
    this->key = key;
    this->forward = new Node* [level + 1];
    std::memset(forward, 0, sizeof(Node* [level + 1]));
}

SkipList::SkipList(uint64_t max_level, float threshold) {
    this->maximal_level = max_level;
    this->threshold = threshold;
    current_level = 0;
    header = new Node(-1, max_level);
}

uint64_t SkipList::coin_flip() {
    float probabillity_of_edge = static_cast<float>(rand()) / RAND_MAX;
    uint64_t level = 0;
    while (probabillity_of_edge < threshold && level < maximal_level) {
        level++;
        probabillity_of_edge = static_cast<float>(rand()) / RAND_MAX;
    }
    return level;
}

Node* SkipList::create_node(int key, uint64_t level) {
    Node* node = new Node(key, level);
    return node;
}
