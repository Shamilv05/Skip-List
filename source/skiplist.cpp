#include "skiplist.hpp"

Node::Node(int value, uint64_t level) {
    this->key = value;
    this->forward = std::vector<std::shared_ptr<Node>>(level + 1);
}

SkipList::SkipList(uint64_t max_level, float prob_threshold) {
    maximal_level = max_level;
    threshold = prob_threshold;
    number_of_levels = 0;
    header = std::make_shared<Node>(-1, max_level);
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

std::shared_ptr<Node> SkipList::create_node(int key, uint64_t level) {
    std::shared_ptr<Node> node = std::make_shared<Node>(key, level);
    return node;
}

void SkipList::insert_element(int value) {
    std::shared_ptr<Node> current = header;

    std::vector<std::shared_ptr<Node>> update(maximal_level + 1);

    for (int i = number_of_levels; i >= 0; i--) {
        while(current->forward[i] != nullptr && current->forward[i]->key < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current == nullptr || current->key != value) {
        uint64_t amount_of_levels = coin_flip();

        if (amount_of_levels > number_of_levels) {
            for (size_t i = number_of_levels + 1; i < amount_of_levels + 1; i++) {
                update[i] = header;
            }
            number_of_levels = amount_of_levels;
        }
        
        std::shared_ptr<Node> node = create_node(value, amount_of_levels);

        for (size_t i = 0; i <= amount_of_levels; i++) {
            node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = node;
        }
    }

    std::cout << "Key " << value << " successfully inserted" << std::endl;
}

void SkipList::search_element(int value) {
    std::shared_ptr<Node> searcher = header;

    for (int i = number_of_levels; i >= 0; i--) {
        while (searcher->forward[i] && searcher->forward[i]->key < value) {
            searcher = searcher->forward[i];
        }
    }

    searcher = searcher->forward[0];

    if (searcher && searcher->key == value) {
        std::cout << "Key found in Skip List: " << value << std::endl;
    } else {
        std::cout << "Key is not found in Skip List: " << value << std::endl;
    }
}

void SkipList::delete_element(int value) {
    std::shared_ptr<Node> current = header;

    std::vector<std::shared_ptr<Node>> update(maximal_level + 1);

    for (int i = number_of_levels; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != nullptr && current->key == value) {
        for (int i = 0; i <= number_of_levels; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
    }

    while (number_of_levels > 0 && header->forward[number_of_levels] == nullptr) {
        number_of_levels--;
    }
}

void SkipList::dump() {
    std::cout << "Skip List dump: begin" << std::endl;
    for (uint64_t i = 0; i <= number_of_levels; i++) {
        std::cout << "Level " << i << ": " << "header -> ";
        std::shared_ptr<Node> node = header->forward[i];
        while(node != nullptr) {
            std::cout << node->key << " -> ";
            node = node->forward[i];
        }
        std::cout << "end" << std::endl;
    }
    std::cout << "Skip List dump: end" << std::endl;
}
