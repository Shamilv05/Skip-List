#include <iostream>
#include "skiplist.hpp"

extern int max_level;

int main() {
    SkipList<int> *S = new SkipList<int>();
    std::vector<Node<int>*> predecessors(max_level + 1);
    std::vector<Node<int>*> successors(max_level + 1);
    S->search(5, predecessors, successors);
    S->insert(5);
    S->insert(15);
    S->insert(115);
    S->dump();

    S->remove(5);
    S->dump();
}
