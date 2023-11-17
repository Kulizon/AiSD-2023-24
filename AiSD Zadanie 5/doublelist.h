// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_back(const T& item); // O(1)
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(1)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)

    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
DoubleList<T>::~DoubleList() {
    clear();
}

template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) {
    head = tail = nullptr;
    DoubleNode<T> *current = other.head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other) {
    if (this != &other) {
        clear();
        DoubleNode<T> *current = other.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
int DoubleList<T>::size() const {
    int count = 0;
    DoubleNode<T> *current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T> *current = head;
    while (current != nullptr) {
        std::cout << current->value;
        current = current->next;
    }
    std::cout << std::endl;
}


template <typename T>
void DoubleList<T>::display_reversed() {
    DoubleNode<T> *current = tail;
    while (current != nullptr) {
        std::cout << current->value;
        current = current->next;
    }
    std::cout << std::endl;
}


template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail = new DoubleNode<T>(item, nullptr, tail);
        tail->prev->next = tail;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::clear() {
     while (!empty()) {
        pop_front();
    }
}


template <typename T>
void DoubleList<T>::pop_front() {
    if (!empty()) {
        DoubleNode<T> *temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }
}

template <typename T>
void DoubleList<T>::pop_back() {
    if (!empty()) {
        DoubleNode<T> *temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            delete temp;
            tail->next = nullptr;
        }
    }
}


#endif

// EOF