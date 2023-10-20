#include "arraylist.h"

int main() {
    ArrayList<int> list(10);

    // test empty()
    assert(list.empty());

    // test push_back
    for (int i = 1; i <= list.max_size(); i++) {
        list.push_back(i * 10);
        assert(list.size() == i);
    }

    list.display();
    std::cout << std::endl;

    // test full()
    assert(list.full());
    
    // test push_front
    list.push_front(100);    
    assert(list.size() == list.max_size());

    // test pop_front
    list.pop_front();
    assert(list.size() == list.max_size() - 1);

    // test pop_back
    list.pop_back();
    assert(list.size() == list.max_size() - 2);

    // test front() and back()
    assert(list.front() == 20);
    assert(list.back() == 90);

    // test clear()
    list.clear();
    assert(list.empty());

    // test reverse
    for (int i = 1; i <= 6; i++) {
        list.push_back(i * 10);
    }
    std::cout << "test reverse" << std::endl;
    list.display();
    list.reverse();
    list.display();
    std::cout << std::endl;
    assert(list.front() == 60);
    assert(list.back() == 10);

    // test sort 
    std::cout << "test sort" << std::endl;
    list.sort();
    list.display();
    std::cout << std::endl;

    std::cout << "Testy zakonczone sukcesem!" << std::endl;
}