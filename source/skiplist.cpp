#include "skiplist.hpp"

Node::Node(int key, uint64_t level) {
    this->key = key;
    this->forward = new Node* [level + 1];
    std::memset(forward, 0, sizeof(Node* [level + 1]));
}

SkipList::SkipList(uint64_t max_level, float threshold) {
    this->maximal_level = max_level;
    this->threshold = threshold;
    number_of_levels = 0;
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

void SkipList::insert_element(int key) {
    Node* current = header;

    Node* update[maximal_level + 1];
    memset(update, 0, sizeof(Node*) * maximal_level);

    for (size_t i = number_of_levels; i >= 0; i--) {
        while(current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current == nullptr || current->key != key) {
        int amount_of_levels = coin_flip();

        if (amount_of_levels > number_of_levels) {
            for (size_t i = number_of_levels + 1; i < amount_of_levels + 1; i++) {
                update[i] = header;
            }
            number_of_levels = amount_of_levels;
        }
        
        Node* node = create_node(key, amount_of_levels);

        for (size_t i = 0; i < amount_of_levels; i++) {
            node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = node;
        }
    }

    std::cout << "Key " << key << " successfully inserted" << std::endl;
}
