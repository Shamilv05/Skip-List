#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include "atomic_markable_reference.hpp"
#include "node.hpp"

extern int max_level;

int get_number_of_levels() {
    int levels = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    float result = dis(gen);
    while (result < 0.5 && levels < max_level) {
        levels += 1;
        result = dis(gen);
    }
    return levels;
}

template<class T> class SkipList {
    Node<T> *head;
    Node<T> *tail;
public:
    SkipList() {
        head = new Node<T>(INT_MIN, 0);
        tail = new Node<T>(INT_MAX, 0);
        for(int i = 0; i <= max_level; i++) {
            head->next[i].set(tail, false);
        }
    }

    bool search(int n_value, std::vector<Node<T>*>& predecessors, std::vector<Node<T>*>& successors) {
        int bottom_level = 0;
        bool *mark = new bool;
        bool snip;

        Node<T> *predecessor = new Node<T>();
		Node<T> *current = new Node<T>();
	    Node<T> *successor = new Node<T>();

        RETRY:
        while(true) {
            predecessor = head;
            for(int i = max_level; i >= bottom_level; i--) {
                current = predecessor->next[i].getReference();
                while(true) {
                    successor = current->next[i].get(mark);
                    while(mark[0]) {
                        snip = predecessor->next[i].CAS(current, successor, false, false);
                        if (!snip) {
                            goto RETRY;
                        }
                        current = predecessor->next[i].getReference();
						successor = current->next[i].get(mark);
                    }
                    if (current->key < n_value) {
                        predecessor = current;
                        current = successor;
                    } else {
                        break;
                    }
                }
                predecessors[i] = predecessor;
                successors[i] = current;
            }
            return (current->key == n_value);
        }

    }

    bool insert(int key, T element = 0) {
        int level = get_number_of_levels();
        int bottom_level = 0;
        std::vector<Node<T>*> predecessors(max_level + 1);
        std::vector<Node<T>*> successors(max_level + 1);
        bool found = search(key, predecessors, successors);

        while(true) {
            bool found = search(key, predecessors, successors);

            if (found) {
                return false;
            } 

            Node<T> *new_node = new Node<T>(key, element, level);

            for (int i = bottom_level; i <= level; i++) {
                new_node->next[i].set(successors[i], false);
            }

            Node<T> *predecessor = predecessors[bottom_level];
            Node<T> *successor = successors[bottom_level];

            if (!predecessor->next[bottom_level].CAS(successor, new_node, false, false)) {
                continue;
            }

            bool *mark = new bool;
            new_node->next[bottom_level].get(mark);
            for(int i = bottom_level + 1; i <= level; i++) {
                while(true) {
                    predecessor = predecessors[i];
                    successor = successors[i];
                    if (predecessor->next[i].CAS(successor, new_node, false, false)) {
                        break;
                    }
                    search(key, predecessors, successors);
                }
            }
            return true;
        }
    }

    bool remove(T x) {
        int bottom_level = 0;

        std::vector<Node<T>*> predecessors(max_level + 1);
        std::vector<Node<T>*> successors(max_level + 1);
        Node<T>* successor = nullptr;

        while(true) {
            bool found = search(x, predecessors, successors);
            if (!found) {
                return false;
            }

            Node<T>* node_to_remove = successors[bottom_level];
            for (int i = node_to_remove->top_level; i >= bottom_level + 1; i--) {
                bool *marked = new bool(false);
                successor = node_to_remove->next[i].get(marked);
                while(!marked[0]) {
                    node_to_remove->next[i].CAS(successor, successor, false, true);
                    successor = node_to_remove->next[i].get(marked);
                }
            }
            bool *marked = new bool(false);
            successor = node_to_remove->next[bottom_level].get(marked);
            while (true) {
                bool marked_it = node_to_remove->next[bottom_level].CAS(successor, successor, false, true);
                successor = successors[bottom_level]->next[bottom_level].get(marked);
                if (marked_it) {
                    search(x, predecessors, successors);
                    return true;
                } else if (marked[0]) {
                    return false;
                }
            }
        }
    }

    void dump() {
        std::cout << "Dump BEGINS" << std::endl;
        for (int i = max_level; i >= 0; i--) {
            Node<T> *temp = head->next[i].getReference();
            std::cout << "Level " << i << ":   head -> ";
            while(temp->next[i].getReference() != NULL)
            {
                std::cout << temp->key << " -> ";
                temp = temp->next[i].getReference();
            }
            std::cout << "tail" << std::endl;
        }
        std::cout << "Dump ENDS" << std::endl;
    }
};

#endif
