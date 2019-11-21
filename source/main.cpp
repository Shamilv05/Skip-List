#include <iostream>
#include "skiplist.hpp"

int main() {
    SkipList lst(10, 0.5);

    lst.insert_element(3); 
    lst.insert_element(6); 
    lst.insert_element(7); 
    lst.insert_element(9); 
    lst.insert_element(12); 
    lst.insert_element(19); 
    lst.insert_element(17); 
    lst.insert_element(26); 
    lst.insert_element(21); 
    lst.insert_element(25); 
    lst.dump(); 
}
