#include <iostream>
#include "doublelist.h"

int main() {
    DoubleList<int> myList;

    // test push_front
    myList.push_front(3);
    myList.push_front(2);
    myList.push_front(1);

    std::cout << "List after push_front: ";
    myList.display(); 

    // test push_back
    myList.push_back(4);
    myList.push_back(5);

    std::cout << "List after push_back: ";
    myList.display(); 

    // test pop_front
    myList.pop_front();

    std::cout << "List after pop_front: ";
    myList.display(); 

    // test pop_back
    myList.pop_back();

    std::cout << "List after pop_back: ";
    myList.display(); 

    // test clear
    myList.clear();

    std::cout << "List after clear: ";
    myList.display(); 

    // test copy constructor
    DoubleList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    std::cout << "Original list: ";
    list1.display(); 

    DoubleList<int> list2(list1);

    std::cout << "Copied list using copy constructor: ";
    list2.display(); 

    // test assignment operator
    DoubleList<int> list3;
    list3.push_back(4);
    list3.push_back(5);

    std::cout << "Original list before assignment: ";
    list3.display(); 

    list3 = list1;

    std::cout << "List after assignment operator: ";
    list3.display(); 

    list3.pop_front();
    list2.pop_front();
    std::cout << "First list before pop operations: ";
    list1.display(); 

    return 0;
}
