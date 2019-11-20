#include "skiplist.hpp"

Node::Node(int key, uint64_t level) {
    this->key = key;
    this->forward = new Node*[level + 1];
    std::memset(forward, 0, sizeof(Node *[level + 1]));
}

SkipList::SkipList(uint64_t max_level, float fraction) {
    this->maximal_level = max_level;
    this->fraction_of_nodes = fraction;
    current_level = 0;
    header = new Node(-1, max_level);
}

int SkipList::randomLevel() {
    float probabillity_of_edge = static_cast<float>(rand()) / RAND_MAX;
    uint64_t level = 0;
    while (probabillity_of_edge < fraction_of_nodes && level < maximal_level) {
        level++;
        probabillity_of_edge = static_cast<float>(rand()) / RAND_MAX;
    }
    return level;
}

