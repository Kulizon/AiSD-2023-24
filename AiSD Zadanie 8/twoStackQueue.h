#include <iostream>
#include <stack>
#include <cassert>
#include <vector>
#include <forward_list>


template <typename T>
class TwoStackQueue {
    std::stack<T> inStack;  // stos do dodawania elementów
    std::stack<T> outStack; // stos do usuwania elementów

public:
    void push(const T& item) {
        inStack.push(item);
    }

    void pop() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }

        if (!outStack.empty()) {
            outStack.pop();
        }
    }

    T& front() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }

        if (!outStack.empty()) {
            return outStack.top();
        }

        throw std::out_of_range("Queue is empty");
    }
    
    T& back() {
        if (inStack.empty()) {
            while (!outStack.empty()) {
                inStack.push(outStack.top());
                outStack.pop();
            }
        }

        if (!inStack.empty()) {
            return inStack.top();
        }

        throw std::out_of_range("Queue is empty");
    }

    bool empty() const {
        return inStack.empty() && outStack.empty();
    }

    int size() const {
        return inStack.size() + outStack.size();
    }
    
    void clear() {
        while (!inStack.empty()) {
            inStack.pop();
        }
        while (!outStack.empty()) {
            outStack.pop();
        }
    }
};
