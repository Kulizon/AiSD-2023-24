#include <iostream>
#include <stack>
#include <cassert>
#include <vector>
#include <forward_list>

#include "listQueue.h"
#include "twoStackQueue.h"

void testListImplementation() {
    ListQueue<int> myQueue;

    // push elements
    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);
    
    std::cout << "Queue: ";
    myQueue.display();

    // test front and back
    assert(myQueue.front() == 1);
    assert(myQueue.back() == 3);
    std::cout << "Front: " << myQueue.front() << std::endl;
    std::cout << "Back: " << myQueue.back() << std::endl;

    // test pop
    myQueue.pop();
    assert(myQueue.front() == 2);
    std::cout << "After pop: ";
    myQueue.display();

    // test size
    assert(myQueue.size() == 2);
    std::cout << "Queue size: " << myQueue.size() << std::endl;
    
    // test clear
    myQueue.clear();
    assert(myQueue.size() == 0);
    std::cout << "After clear: ";
    myQueue.display();
    
    // test copy constructor and = operator
    ListQueue<int> originalQueue;
    originalQueue.push(1);
    originalQueue.push(2);
    originalQueue.push(3);

    ListQueue<int> copiedQueue(originalQueue);

    // check sizes
    assert(originalQueue.size() == copiedQueue.size());

    // check elements
    assert(originalQueue.front() == copiedQueue.front());
    assert(originalQueue.back() == copiedQueue.back());

    // modify original queue
    originalQueue.pop();
    originalQueue.push(4);

    // compare fronts and backs
    assert(originalQueue.front() != copiedQueue.front());
    assert(originalQueue.back() != copiedQueue.back());

    // copy constructor
    ListQueue<int> assignedQueue = originalQueue;

    // check sizes
    assert(originalQueue.size() == assignedQueue.size());

    // check elements
    assert(originalQueue.front() == assignedQueue.front());
    assert(originalQueue.back() == assignedQueue.back());

    std::cout << "Copy constructor and = operator tests passed" << std::endl;
    std::cout << "List implementation tests passed" << std::endl;
}



void TestStackImplementation() {
    TwoStackQueue<int> myQueue;

    // push elements
    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);

    // test front and back
    assert(myQueue.front() == 1);
    assert(myQueue.back() == 3);
    std::cout << "Front: " << myQueue.front() << std::endl;
    std::cout << "Back: " << myQueue.back() << std::endl;

    // test pop
    myQueue.pop();
    assert(myQueue.front() == 2);

    // test size
    assert(myQueue.size() == 2);
    std::cout << "Queue size: " << myQueue.size() << std::endl;
    
    // test clear
    myQueue.clear();
    assert(myQueue.size() == 0);
    
    // test copy constructor and = operator
    TwoStackQueue<int> originalQueue;
    originalQueue.push(1);
    originalQueue.push(2);
    originalQueue.push(3);

    TwoStackQueue<int> copiedQueue(originalQueue);

    // check sizes
    assert(originalQueue.size() == copiedQueue.size());

    // check elements
    assert(originalQueue.front() == copiedQueue.front());
    assert(originalQueue.back() == copiedQueue.back());

    // modify original queue
    originalQueue.pop();
    originalQueue.push(4);

    // compare fronts and backs
    assert(originalQueue.front() != copiedQueue.front());
    assert(originalQueue.back() != copiedQueue.back());

    // copy constructor
    TwoStackQueue<int> assignedQueue = originalQueue;

    // check sizes
    assert(originalQueue.size() == assignedQueue.size());

    // check elements
    assert(originalQueue.front() == assignedQueue.front());
    assert(originalQueue.back() == assignedQueue.back());

    std::cout << "Copy constructor and = operator tests passed" << std::endl;
    std::cout << "Stack implementation tests passed" << std::endl;
}

int main() {
    testListImplementation();
    std::cout << std::endl;
    TestStackImplementation();
    
    return 0;
}












