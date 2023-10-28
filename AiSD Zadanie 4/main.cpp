#include <iostream>
#include "singlelist.h"

int main() {
    SingleList<int> *myList = new SingleList<int>();

    // create initial list
    std::cout << std::endl << "Create list" << std::endl;
    myList->display();
    myList->push_front(2);
    myList->push_front(3);
    myList->push_front(4);
    myList->display();

    // testing reverse
    std::cout << std::endl << "Test reverse" << std::endl;
    assert(myList->front() == 4); 
    myList->reverse();
    assert(myList->front() == 2); 
    myList->display();

    // testing = operator
    std::cout << std::endl << "Test '=' operator" << std::endl;
    SingleList<int> *myCopiedList = new SingleList<int>();
    myCopiedList->push_back(1);
    myCopiedList->display();
    myCopiedList = myList;
    myCopiedList->display();
    assert(myCopiedList->front() == 2); 
    
    // testing copy constructor
    std::cout << std::endl << "Test copy constructor" << std::endl;
    myCopiedList->push_front(9);
    myCopiedList->push_back(6);
    SingleList<int> *myThirdList(myCopiedList);
    myThirdList->display();
    std::cout << "Size: " << myThirdList->size() << std::endl;
    assert(myThirdList->size() == 5);
    assert(myThirdList->front() == 9);
    assert(myThirdList->back() == 6);


    // testing pop functions
    std::cout << std::endl << "Test pop functions" << std::endl;
    myThirdList->pop_back();
    myThirdList->pop_front();
    myThirdList->display();
    assert(myThirdList->size() == 3);
    assert(myThirdList->front() == 2);
    assert(myThirdList->back() == 4);

    // testing clear function
    std::cout << std::endl << "Test clear function" << std::endl;
    myList->clear();
    assert(myThirdList->size() == 0);
    myList->display();
}