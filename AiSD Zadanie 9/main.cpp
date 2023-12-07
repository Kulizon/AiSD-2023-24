#include <iostream>
#include <algorithm>   // make_heap, push_heap, pop_heap
#include <vector>
#include <cassert>

template <typename T>
class MyPriorityQueue {
    std::vector<T> lst; // działa domyślny konstruktor dla std::vector
public:
    MyPriorityQueue(int s=10) { 
        lst.reserve(s);
    } // default constructor
    
    ~MyPriorityQueue() { 
        lst.clear();
    }
    
    MyPriorityQueue(const MyPriorityQueue& other) {
        std::copy(other.lst.begin(), other.lst.end(), std::back_inserter(lst));
        std::make_heap(lst.begin(), lst.end());
        
    }; // copy constructor
    MyPriorityQueue(MyPriorityQueue&& other) {
        lst = std::move(other.lst);
    }; // move constructor 
    MyPriorityQueue& operator=(const MyPriorityQueue& other) {
        if (this != &other) {
            lst.resize(other.lst.size());
            std::copy(other.lst.begin(), other.lst.end(), std::back_inserter(lst));
            std::make_heap(lst.begin(), lst.end());
        }
        return *this;
    }; // copy assignment operator, return *this
    MyPriorityQueue& operator=(MyPriorityQueue&& other) {
        if (this != &other) {
            lst = std::move(other.lst);
        }
        return *this;
    }; // move assignment operator, return *this
    
    bool empty() const { 
        return lst.empty();
    }
    
    int size() const { 
        return lst.size();
    } // liczba elementów w kolejce
    
    void push(const T& item) { // dodanie do kolejki
        lst.push_back(item);
        std::push_heap(lst.begin(), lst.end());
    }
    
    void push(T&& item) { // dodanie do kolejki
        lst.push_back(std::move(item));
        std::push_heap(lst.begin(), lst.end());
    }
    
    T& top() { 
        return lst.front();
    } // zwraca element największy, nie usuwa
    
    void pop() { // usuwa element największy
        std::pop_heap(lst.begin(), lst.end());
        lst.pop_back();
    }
    
    void clear() { 
        lst.clear();
    } // czyszczenie listy z elementów
    
    void display() {
        for (const auto& item : lst) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    };
};

int main() {
    MyPriorityQueue<int> pq;

    // Test push and top
    pq.push(3);
    pq.push(1);
    pq.push(4);
    std::cout << "Powinno wypisać: 4, top po operacji push: " << pq.top() << std::endl;
    assert(pq.top() == 4);
    pq.clear();

    // Test push and pop
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.pop();
    std::cout << "Powinno wypisać: 3, top po operacji pop: " << pq.top() << std::endl;
    assert(pq.top() == 3);
    pq.clear();

    // Test empty
    std::cout << "Czy pusta na początku? " << (pq.empty() ? "Tak" : "Nie") << std::endl;
    assert(pq.empty());
    pq.push(42);
    std::cout << "Czy pusta po operacji push? " << (pq.empty() ? "Tak" : "Nie") << std::endl;
    assert(!pq.empty());
    pq.pop();
    std::cout << "Czy pusta po operacji pop? " << (pq.empty() ? "Tak" : "Nie") << std::endl;
    assert(pq.empty());
    pq.clear();

    // Test size
    std::cout << "Rozmiar pustej: " << pq.size() << std::endl;
    assert(pq.size() == 0);
    pq.push(1);
    pq.push(2);
    pq.push(3);
    std::cout << "Powinno wypisać: 3, rozmiar po trzech operacjach push: " << pq.size() << std::endl;
    assert(pq.size() == 3);
    pq.pop();
    std::cout << "Powinno wypisać: 2, rozmiar po operacji pop: " << pq.size() << std::endl;
    assert(pq.size() == 2);
    pq.clear();

    // Test clear
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.clear();
    std::cout << "Czy pusta po operacji clear? " << (pq.empty() ? "Tak" : "Nie") << std::endl;
    assert(pq.empty());

    // Test move constructor
    pq.push(1);
    pq.push(2);
    pq.push(3);
    MyPriorityQueue<int> pq2(std::move(pq));
    std::cout << "Czy oryginalna kolejka jest pusta po użyciu move constructor? " << (pq.empty() ? "Tak" : "Nie") << std::endl;
    std::cout << "Powinno wypisać: 3, top po użyciu move constructor? " << pq2.top() << std::endl;
    assert(pq.empty());
    assert(pq2.top() == 3);
    pq.clear();

    // Test move assignment operator
    pq.push(1);
    pq.push(2);
    pq.push(3);
    MyPriorityQueue<int> pq3;
    pq3 = std::move(pq);
    std::cout << "Czy oryginalna kolejka jest pusta po użyciu move assignment? " << (pq.empty() ? "Tak" : "Nie") << std::endl;
    std::cout << "Powinno wypisać: 3, top po użyciu move assignment? " << pq3.top() << std::endl;
    assert(pq.empty());
    assert(pq3.top() == 3);
    pq.clear();

    // Test copy constructor
    pq.push(1);
    pq.push(2);
    pq.push(3);
    MyPriorityQueue<int> pq4(pq);
    pq4.push(4);
    std::cout << "Powinno wypisać: 3, top oryginalnej po użyciu copy constructor: " << pq.top() << std::endl;
    std::cout << "Powinno wypisać: 4, top nowej po użyciu copy constructor:  " << pq4.top() << std::endl;
    assert(pq.top() == 3);
    assert(pq4.top() == 4);
    pq.clear();

    // Test copy assignment operator
    pq.push(1);
    pq.push(2);
    pq.push(3);
    MyPriorityQueue<int> pq5;
    pq5 = pq;
    pq5.push(4);
    std::cout << "Powinno wypisać: 3, top oryginalnej po użyciu copy assignment: " << pq.top() << std::endl;
    std::cout << "Powinno wypisać: 4, top nowej po użyciu copy assignment: " << pq5.top() << std::endl;
    assert(pq.top() == 3);
    assert(pq5.top() == 4);
    pq.clear();

    std::cout << "Wszystkie testy zakończone." << std::endl;

    return 0;
}


