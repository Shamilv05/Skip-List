#include <iostream>
#include "skiplist.hpp"

int main() {
    SkipList lst(20, 0.5);

    lst.insert_element(2); 
    lst.insert_element(6); 
    lst.insert_element(7); 
    lst.insert_element(9); 
    lst.insert_element(12); 
    lst.insert_element(19); 
    lst.insert_element(17); 
    lst.insert_element(26); 
    lst.insert_element(21); 
    lst.insert_element(25);
    lst.insert_element(12); 
    lst.insert_element(129); 
    lst.insert_element(126); 
    lst.insert_element(121); 
    lst.insert_element(125);
    lst.insert_element(1129); 
    lst.insert_element(1126); 
    lst.insert_element(1121); 
    lst.insert_element(1125);

    lst.dump(); 

    lst.search_element(12);
    lst.search_element(1125);

    lst.delete_element(12);
    lst.delete_element(1125);

    lst.search_element(12);
    lst.search_element(1125);
}
