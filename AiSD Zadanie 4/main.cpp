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

    myList->clear();
    myList->display();
}