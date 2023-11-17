#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()


// mydeque.h
template <typename T>
class MyDeque {
    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja
public:
    MyDeque(int s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor
    ~MyDeque() { 
        delete [] tab;
    }
    MyDeque(const MyDeque& other); // copy constructor

    MyDeque& operator=(const MyDeque& other); // copy assignment operator, return *this

    bool empty() const { 
        return head == tail;
    }
    bool full() const { 
        return (tail + 1) % msize == head;
    }
    int size() const { 
        return (tail - head + msize) % msize; 
    }
    int max_size() const { 
        return msize-1;
    }
    void push_front(const T& item); // dodanie na początek O(1)

    void push_back(const T& item); // dodanie na koniec O(1)

    T& front() { 
        return tab[head];
    } // zwraca poczatek
    T& back() { 
        return tab[(tail + msize -1) % msize];
    } // zwraca koniec
    
    void pop_front(); // usuwa początek kolejki O(1)
    void pop_back(); // usuwa koniec kolejki O(1)
    void clear(); // czyszczenie listy z elementów

    void display();
    
};

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other) {
        msize = other.msize;
        tab = new T[msize];

        head = other.head;
        tail = other.tail;
        for (int i = head; i != tail; i = (i + 1) % msize) {
            tab[i] = other.tab[i];
        }
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) {
    if (this != &other) {
        clear();

        msize = other.msize;
        tab = new T[msize];

        head = other.head;
        tail = other.tail;
        for (int i = head; i != tail; i = (i + 1) % msize) {
            tab[i] = other.tab[i];
        }
    }
    return *this;
}

template <typename T>
void MyDeque<T>::clear() {
    while(!empty()) {
        pop_front();
    }
}


template <typename T>
void MyDeque<T>::pop_front() {
    if (!empty()) {
        head = (head + 1) % msize;
    }
}

template <typename T>
void MyDeque<T>::pop_back() {
    if (!empty()) {
        tail = (tail - 1 + msize) % msize;
    }
}

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    head = (head + msize -1) % msize;
    tab[head] = item;
}
template <typename T>
void MyDeque<T>::push_back(const T& item) {
    tab[tail] = item;
    tail = (tail + 1) % msize;
}
template <typename T>
void MyDeque<T>::display() {
    for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

#endif