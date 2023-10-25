#include <iostream>
#include "singlelist.h"

int main() {
    SingleList<int> *myList = new SingleList<int>();

    myList->display();
    myList->push_front(2);
    myList->push_front(3);
    myList->push_front(4);
    myList->display();

    myList->reverse();

    myList->display();

    SingleList<int> *myCopiedList = new SingleList<int>();
    myCopiedList->push_back(1);
    myCopiedList = myList;

    myCopiedList->display();

    SingleList<int> *myThirdList(myList);

    std::cout << std::endl;
    myThirdList->display();
    std::cout << "Size: " << myThirdList->size() << std::endl;
    
    myThirdList->pop_back();
    myThirdList->pop_back();

    std::cout << std::endl;
    myThirdList->display();
    std::cout << "Size: " << myThirdList->size() << std::endl;

    myList->clear();
    myList->display();
}