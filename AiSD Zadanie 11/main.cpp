#include <iostream>
#include <stack>
#include <climits>
#include <time.h>
#include <stdio.h>

template <typename T>
struct BSTNode {
    T value;
    BSTNode<T> *left, *right;

    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() {}
};

template <typename T>
class MyTree {
    BSTNode<T> *root;

public:
    MyTree() : root(nullptr) {}
    MyTree(const T& rootValue) : root(new BSTNode<T>(rootValue)) {}
    ~MyTree() { clear(); }

    void insert(const T& item) { root = insert(root, item); }
    void display() { display(root, 0); }
    void clear() { clear(root); root = nullptr; }
    
    BSTNode<T>* find_min() {
        if (!root) return nullptr;
        return find_min_h(root);
    }

    BSTNode<T>* find_min_h(BSTNode<T>* node) {
        if (node->left) return find_min_h(node->left);
        else return node;
    }

    BSTNode<T>* find_max() {
        if (!root) return nullptr;
        return find_max_h(root);
    }

    BSTNode<T>* find_max_h(BSTNode<T>* node) {
        if (node->right) return find_max_h(node->right);
        else return node;
    }

    bool isBST() {
        if (!root) return false;
        return isBST(root, INT_MIN, INT_MAX);
    }

    bool isBST(BSTNode<T>* top, T minKey, T maxKey) {
        if (top == nullptr) {
            return true;
        }

        if (top->value < minKey || top->value > maxKey) {
            return false;
        }

        return isBST(top->left, minKey, top->value) && isBST(top->right, top->value, maxKey);
    }
    

private:
    BSTNode<T> *insert(BSTNode<T> *node, const T& item) {
        if (node == nullptr) {
            return new BSTNode<T>(item);
            // return new BSTNode<T>(item + (int)(rand() % 2 - 2));
            // jeżeli dodamy losową zmiane wartości, to nasze drzewa przestaną być BST
        }

        if (item < node->value) {
            node->left = insert(node->left, item);
        } else {
            node->right = insert(node->right, item);
        }

        return node;
    }

    void display(BSTNode<T> *node, int level) {
        if (node == nullptr) return;

        display(node->right, level + 1);
        std::cout << std::string(3 * level, ' ') << node->value << std::endl;
        display(node->left, level + 1);
    }

    void clear(BSTNode<T> *node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

int main() {
    MyTree<int> myTree(5);
    myTree.insert(8);
    myTree.insert(3);
    myTree.insert(7);
    myTree.insert(4);
    myTree.insert(9);
    myTree.insert(2);
    std::cout << "Drzewo 1:" << std::endl;
    myTree.display();
    std::cout << "(Oczekiwano: 9) Maksymalna wartość: " << myTree.find_max()->value << std::endl;
    std::cout << "(Oczekiwano: 2) Minimalna wartość: " << myTree.find_min()->value  << std::endl;
    std::cout << "(Oczekiwano: True) Czy to drzewo BST?: " << (myTree.isBST() ? "True" : "False") << std::endl;
    std::cout << std::endl;
    
    MyTree<int> myEmptyTree;
    std::cout << "Drzewo 2 (puste):" << std::endl;
    myEmptyTree.display();
    if (myEmptyTree.find_max()) {
        std::cout << "To nie powinno się wydrukować!" << std::endl;
    } else {
        std::cout << "Brak maksymalnej wartości dla pustego drzewa." << std::endl;
    }
    if (myEmptyTree.find_min()) {
        std::cout << "To nie powinno się wydrukować!" << std::endl;
    } else {
        std::cout << "Brak maksymalnej wartości dla pustego drzewa." << std::endl;
    }
    std::cout << "(Oczekiwano: False) Czy to drzewo BST?: " << (myEmptyTree.isBST() ? "True" : "False") << std::endl;
    std::cout << std::endl;
    
    MyTree<int> mySecondTree;
    mySecondTree.insert(3);
    mySecondTree.insert(2);
    mySecondTree.insert(1);
    mySecondTree.insert(5);
    std::cout << "Drzewo 3:" << std::endl;
    mySecondTree.display();
    std::cout << "(Oczekiwano: 5) Maksymalna wartość:  " << mySecondTree.find_max()->value  << std::endl;
    std::cout << "(Oczekiwano: 1) Minimalna wartość: " << mySecondTree.find_min()->value  << std::endl;
    std::cout << "(Oczekiwano: True) Czy to drzewo BST?: " << (mySecondTree.isBST() ? "True" : "False") << std::endl;
    std::cout << std::endl;
}