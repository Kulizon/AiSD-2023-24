#include <iostream>
#include <stack>

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
    
    int calc_leafs_iter() {
        if (root == nullptr) return 0;
        
        std::stack<BSTNode<T>*> stack;
        stack.push(root);
        
        int c = 0;
        
        while(!stack.empty()) {
            BSTNode<T> *node = stack.top();
            stack.pop();
            
            if (!node->left && !node->right) c += 1;
            if (node->left) stack.push(node->left);
            if(node->right) stack.push(node->right);
        }
        
        return c;
    }
    
    int calc_leafs_rec(BSTNode<T> *node) {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        
        return calc_leafs_rec(node->left) + calc_leafs_rec(node->right);
    }
    
    int calc_leafs_rec() {
        if (root == nullptr) return 0;
        
        return calc_leafs_rec(root);
    }
    
    int calc_total_iter() {
        if (root == nullptr) return 0;
        
        std::stack<BSTNode<T>*> stack;
        stack.push(root);
        
        int c = 0;
        
        while(!stack.empty()) {
            BSTNode<T> *node = stack.top();
            stack.pop();
            
            c += node->value;
            if (node->left) stack.push(node->left);
            if(node->right) stack.push(node->right);
        }
        
        return c;
    }
    
    int calc_total_rec(BSTNode<T> *node) {
        if (!node) return 0;
        if (!node->left && !node->right) return node->value;
        
        return calc_total_rec(node->left) + calc_total_rec(node->right) + node->value;
    }
    
    int calc_total_rec() {
        if (root == nullptr) return 0;
        
        return calc_total_rec(root);
    }
    

private:
    BSTNode<T> *insert(BSTNode<T> *node, const T& item) {
        if (node == nullptr) {
            return new BSTNode<T>(item);
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
    std::cout << "(Oczekiwano: 4) Tyle liści rekurenycjnie: " << myTree.calc_leafs_rec() << std::endl;
    std::cout << "(Oczekiwano: 4) Tyle liści iteracyjnie: " << myTree.calc_leafs_iter() << std::endl;
    std::cout << std::endl;
    std::cout << "(Oczekiwano: 38) Suma rekurenycjnie: " << myTree.calc_total_rec() << std::endl;
    std::cout << "(Oczekiwano: 38) Suma iteracyjnie: " << myTree.calc_total_iter() << std::endl;
    std::cout << std::endl;
    
    MyTree<int> myEmptyTree;
    std::cout << "Drzewo 2 (puste):" << std::endl;
    myEmptyTree.display();
    std::cout << "(Oczekiwano: 0) Tyle liści rekurenycjnie: " << myEmptyTree.calc_leafs_rec() << std::endl;
    std::cout << "(Oczekiwano: 0) Tyle liści iteracyjnie: " << myEmptyTree.calc_leafs_iter() << std::endl;
    std::cout << std::endl;
    std::cout << "(Oczekiwano: 0) Suma rekurenycjnie: " << myEmptyTree.calc_total_rec() << std::endl;
    std::cout << "(Oczekiwano: 0) Suma iteracyjnie: " << myEmptyTree.calc_total_iter() << std::endl;
    std::cout << std::endl;
    
    MyTree<int> mySecondTree;
    mySecondTree.insert(3);
    mySecondTree.insert(2);
    mySecondTree.insert(1);
    mySecondTree.insert(5);
    std::cout << "Drzewo 3:" << std::endl;
    mySecondTree.display();
    std::cout << "(Oczekiwano: 2) Tyle liści rekurenycjnie: " << mySecondTree.calc_leafs_rec() << std::endl;
    std::cout << "(Oczekiwano: 2) Tyle liści iteracyjnie: " << mySecondTree.calc_leafs_iter() << std::endl;
    std::cout << std::endl;
    std::cout << "(Oczekiwano: 11) Suma rekurenycjnie: " << mySecondTree.calc_total_rec() << std::endl;
    std::cout << "(Oczekiwano: 11) Suma iteracyjnie: " << mySecondTree.calc_total_iter() << std::endl;
    std::cout << std::endl;
}