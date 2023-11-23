#include <iostream>
#include <array>
#include <vector>
#include <list>

template <typename T>
class MyStack {
    std::list<T> lst;
public:
    MyStack() = default; // default constructor

    MyStack(const MyStack& other) : lst(other.lst) {} // copy constructor

    MyStack& operator=(const MyStack& other) {
        if (this != &other) {
            lst = other.lst;
        }
        return *this;
    } // copy assignment operator, return *this

    bool empty() const {
        return lst.empty();
    } // checks if the container has no elements

    int size() const {
        return static_cast<int>(lst.size());
    }

    void push(const T& item) {
        lst.push_back(item);
    }

    T& top() {
        if (!empty()) {
            return lst.back();
        } else {
            throw std::out_of_range("Stack is empty. Cannot get top element.");
        }
    } // zwraca koniec, nie usuwa

    void pop() {
        if (!empty()) {
            lst.pop_back();
        } else {
            throw std::out_of_range("Stack is empty. Cannot pop.");
        }
    } // usuwa koniec

    void clear() {
        lst.clear();
    }

    void display() {
        for (const T& item : lst) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};


int rpn(std::vector<std::string> input) {
    MyStack<int> stack;
    
    for(unsigned int i = 0; i < input.size(); i++) {
        
        if (input[i] == "+" || input[i] == "-" || input[i] == "/" || input[i] == "*") {
            int el1 = stack.top();
            stack.pop();
            int el2 = stack.top();
            stack.pop();
            
            int res;
            
            if (input[i] == "+") res = el2 + el1;
            if (input[i] == "-") res = el2 - el1;
            if (input[i] == "*") res = el2 * el1;
            if (input[i] == "/") {
                if (el1 == 0) {
                     throw std::invalid_argument("Nie można dzielić przez 0!");
                }
                res = el2 / el1;
                };
            
            stack.push(res);
            
        } else {
            stack.push(std::stoi(input[i]));
        }
        
        
    }
    
    return stack.top();
};




int main()
{
    MyStack<int> stack;
    
    std::cout << "Test push" << std::endl;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.display();
    
    std::cout << "Test top" << std::endl;
    int top = stack.top();
    std::cout << "Expect '4': " << top << std::endl;
    
    std::cout << "Test pop" << std::endl;
    stack.pop();
    stack.display();
    
    std::cout << "Test copy constructor" << std::endl;
    MyStack<int> otherStack(stack);
    otherStack.push(5);
    stack.push(9);
    stack.display();
    otherStack.display();
    
    std::cout << "Test assignment operator" << std::endl; 
    otherStack = stack;
    otherStack.push(6);
    stack.display();
    otherStack.display();
    
    std::cout << std::endl;
    
    // ONP tests
    std::vector<std::string> input1 { "-6", "2", "/" };
    std::vector<std::string> input2 {"3", "5", "*", "2", "8", "-", "2", "/", "+"};
    std::vector<std::string> input3 {"2", "3", "+", "5", "*", "1", "/", "2", "10", "*", "-"};

    std::cout << "Expect -3: " << rpn(input1) << std::endl; // expect: -3
    std::cout << "Expect 12: " << rpn(input2) << std::endl; // expect: 12
    std::cout << "Expect 5: " << rpn(input3) << std::endl; // expect: 5


    return 0;
}
