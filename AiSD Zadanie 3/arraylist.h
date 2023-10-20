#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    ArrayList(int s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~ArrayList() { delete [] tab; } // destruktor

    ArrayList(const ArrayList& other) {
        tab = new T[max_size()];
        for (int i = 0; i < last; i++) {
            tab[i] = other.tab[i];
        }
    }; // copy constructor
    // usage:   ArrayList<int> list2(list1);

    ArrayList& operator=(const ArrayList& other) {
        if (this == &other) {
            return *this;
        }

        delete[] tab;
        msize = other.max_size();
        last = other.last;
        tab = new T[max_size()];

        for (int i = 0; i < last; i++) {
            tab[i] = other.tab[i];
        }

        return *this;
    }; // copy assignment operator, return *this
    // usage:   list2 = list1;


    bool empty() const { 
        return last == 0; // todo: changed this
    } // checks if the container has no elements
    
    bool full() const { 
        return last == msize;
    } // checks if the container is full
    
    int size() const { 
        return last;
    } // liczba elementow na liscie
    
    int max_size() const { 
        return msize;
    } // najwieksza mozliwa liczba elementow
    
    void push_front(const T& item) {
        if (full()) return;

        for (int i = this->last; i > 0; i--) {
            tab[i] = tab[i - 1];
        }

        this->tab[0] = item;
        this->last++;
        
    } // dodanie na poczatek
    

    void push_back(const T& item) {
        if (full()) return;
        
        this->tab[last] = item;
        this->last++;
        
    }; // dodanie na koniec
    
    T& front() {
        assert(!this->empty());
        return this->tab[0];
    }; // zwraca poczatek, nie usuwa, error dla pustej listy
    
    T& back() {
        assert(!this->empty());
        return this->tab[last-1];
    }; // zwraca koniec, nie usuwa, error dla pustej listy
    
    void pop_front() {
        assert(!this->empty());

        this->tab[0] = 0;
        for (int i = 0; i < this->last; i++)
        {
            this->tab[i] = this->tab[i+1];
        }
        this->last--;
    }; // usuwa poczatek, error dla pustej listy
    
    void pop_back() {
        assert(!this->empty());

        this->tab[last-1] = 0;
        this->last--;
    }; // usuwa koniec, error dla pustej listy
    
    void clear() {
        for (int i = 0; i < last; i++)
        {
            this->tab[i] = 0;
        }

        this->last = 0;
    }; // czyszczenie listy z elementow
    
    void display() {
        for (int i = 0; i < last; i++)
        {
            std::cout << this->tab[i] << " "; 
        }
        std::cout << std::endl;
    }; // lepiej zdefiniowac operator<<
    
    void reverse() {
        for (int i = 0; i < (this->size() / 2); i++)
        {
            T temp = this->tab[i];
            this->tab[i] = this->tab[this->last - i - 1];
            this->tab[this->last - i - 1] = temp;
        }
        
        
    }; // odwracanie kolejnosci
    
    void sort() {
        for (int i = 0; i < this->size(); i++)
        {
            for (int j = 0; j < this->size(); j++)
            {
                if (this->tab[i] < this->tab[j]) {
                    T temp = this->tab[i];
                    this->tab[i] = this->tab[j];
                    this->tab[j] = temp;
                }
            }
            
        }
        
    }; // sortowanie listy
    

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif