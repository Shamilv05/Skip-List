#ifndef ATOMIC_MARKABLE_REFERENCE_H
#define ATOMIC_MARKABLE_REFERENCE_H

#include <iostream>
#include <vector>
#include <atomic>
#include <random>

template<class T> struct MarkableReference {
    T* next;
    bool marked;

    MarkableReference() {
        next = nullptr;
        marked = false;
    }

    MarkableReference(T* node, bool mark) {
        next = node;
        marked = mark;
    }

    bool operator==(const MarkableReference<T>& other) {
        return (next == other.next && marked == other.marked);
    }
};

template<class T> class AtomicMarkableReference {
private:
    std::atomic<MarkableReference<T>*> marked_next;
public:
    AtomicMarkableReference() {
        marked_next.store(new MarkableReference<T>(nullptr, false));
    }

    AtomicMarkableReference(T* next_node, bool mark) {
        marked_next.store(new MarkableReference<T>(next_node, mark));
    }

    T* getReference() {
        return marked_next.load()->next;
    }

    T* get(bool *mark) {
        MarkableReference<T> *temp = marked_next.load();
        *mark = temp->marked;
        return temp->next;
    }

    void set(T* new_ref, bool new_mark) {
        MarkableReference<T> *current = marked_next.load();
        if (new_ref != current->next || new_mark != current->marked) {
            marked_next.store(new MarkableReference<T>(new_ref, new_mark));
        }
    }

    bool CAS(T* expected, T* new_value, bool expected_mark, bool new_mark) {
        MarkableReference<T> *curr = marked_next.load();
        return (expected == curr->next && expected_mark == curr->marked && 
			   ((new_value == curr->next && new_mark == curr->marked) ||
		       marked_next.compare_exchange_strong(curr, new MarkableReference<T>(new_value, new_mark))));
    }
};

#endif
