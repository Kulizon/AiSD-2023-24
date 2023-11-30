#include <iostream>
#include <stack>
#include <cassert>
#include <vector>
#include <forward_list>

template <typename T>
class ListQueue {
private:
    std::forward_list<T> container;
public:
    ListQueue() = default; // default constructor

    ~ListQueue() = default;

    ListQueue(const ListQueue& other) {
        for (const auto& item : other.container) {
            push(*(new T(item)));
        }
    } // copy constructor

    ListQueue& operator=(const ListQueue& other) {
        if (this != &other) {
            clear();

            for (const auto& item : other.container) {
                push(*(new T(item)));
            }
        }
        return *this;
    } // copy assignment operator, return *this

    bool empty() const {
        return container.empty();
    } // checks if the container has no elements

    int size() const {
        return std::distance(container.begin(), container.end());
    } // liczba elementów w kolejce

    void push(const T& item) {
        if (empty()) {
            container.push_front(item);
        } else {
            auto it = container.begin();
            while (std::next(it) != container.end()) {
                ++it;
            }
            container.insert_after(it, item);
        }
    } // dodanie na koniec, push_back(item)

    T& front() {
        return container.front();
    } // zwraca początek, nie usuwa

    T& back() {
        auto it = container.begin();
        auto end = container.end();
        auto prev = it;
        while (it != end) {
            prev = it;
            ++it;
        }
        return *prev;
    } // zwraca koniec, nie usuwa

    void pop() {
        if (!empty()) {
            container.pop_front();
        }
    } // usuwa początek kolejki, pop_front()

    void clear() {
        container.clear();
    } // czyszczenie listy z elementów

    void display() {
        for (const auto& item : container) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};