#include <iostream>
#include "mydeque.h"

int main() {

    MyDeque<int> myDeque;
    myDeque.push_back(1);
    myDeque.push_back(2);
    myDeque.push_back(3);

    std::cout << "Original deque: ";
    myDeque.display(); // 1 2 3

    // Test copy constructor
    MyDeque<int> copiedDeque(myDeque);

    std::cout << "Copied deque using copy constructor: ";
    copiedDeque.display(); // 1 2 3

    // Test copy assignment operator
    MyDeque<int> anotherDeque;
    anotherDeque.push_back(4);
    anotherDeque.push_back(5);

    std::cout << "Original deque before assignment: ";
    anotherDeque.display(); // expect: 4 5

    anotherDeque = myDeque;
    anotherDeque.pop_back();

    std::cout << "Deque after copy assignment operator: ";
    anotherDeque.display(); // expect: 1 2

    // Test copy pushes and pops
    std::cout << "Original deque: ";
    myDeque.display(); // expect: 1 2 3
    myDeque.push_front(4);
    myDeque.push_front(5);
    myDeque.push_front(6);
    myDeque.push_front(7);
    myDeque.push_back(8);
    myDeque.push_back(9);
    myDeque.push_back(10);

    myDeque.pop_front();
    myDeque.pop_back();

    std::cout << "Original deque: ";
    myDeque.display(); // expect: 6 5 4 1 2 3 8 9

    std::cout << "Front of myDeque: "; 
    std::cout << myDeque.front() << std::endl; // expect: 6
    std::cout << "Back of myDeque: ";
    std::cout << myDeque.back() << std::endl; // expect: 9


    // Test clear
    myDeque.clear();
    std::cout << "Deque after clear: ";
    myDeque.display(); 

    return 0;
}
