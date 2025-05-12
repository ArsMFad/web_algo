#include <iostream>
#include <stack>
#include <cassert>
#include <functional>
#include <sstream>


template <typename T, typename Compare = std::less<T>>
class BinaryTree {
    struct Node {
        Node(const T &data) 
            : data(data), left(nullptr), right(nullptr) 
        {
        }
        
        T data;
        Node *left;
        Node *right;
    };

public:
    BinaryTree(const Compare& comp = Compare()) 
        : root(nullptr), comp(comp) 
    {
    }
    
    ~BinaryTree() {
        destroyTree(root);
    }
    
    void Add(const T &data) {
        if (!root) {
            root = new Node(data);
            return;
        }
        
        Node* current = root;
        while (true) {
            if (comp(data, current->data)) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = new Node(data);
                    break;
                }
            } else {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = new Node(data);
                    break;
                }
            }
        }
    }
    
    void PrintPreOrder(std::ostream& out) const {
        out << getPreOrderString();
    }
    
    std::string getPreOrderString() const {
        std::stringstream ss;
        if (!root) {
            return ss.str();
        }
        
        std::stack<Node*> stack;
        stack.push(root);
        
        while (!stack.empty()) {
            Node* current = stack.top();
            stack.pop();
            
            ss << current->data << " ";
            
            if (current->right) {
                stack.push(current->right);
            }
            if (current->left) {
                stack.push(current->left);
            }
        }
        return ss.str();
    }

private:
    void destroyTree(Node *node) {
        if (node) {
            std::stack<Node*> stack;
            stack.push(node);
            
            while (!stack.empty()) {
                Node* current = stack.top();
                stack.pop();
                
                if (current->left) {
                    stack.push(current->left);
                }
                if (current->right) {
                    stack.push(current->right);
                }
                
                delete current;
            }
        }
    }
    
    Node *root;
    Compare comp;
};


void solve(std::istream& in, std::ostream& out) {
    int N;
    in >> N;
    assert(N > 0 && N < 1000000);
    
    BinaryTree<int> tree;
    for (int i = 0; i < N; ++i) {
        int num;
        in >> num;
        tree.Add(num);
    }
    
    tree.PrintPreOrder(out);
}


void tests() {
    {
        BinaryTree<int> tree;
        tree.Add(5);
        tree.Add(3);
        tree.Add(7);
        tree.Add(2);
        tree.Add(4);
        tree.Add(6);
        tree.Add(8);
        
        assert(tree.getPreOrderString() == "5 3 2 4 7 6 8 ");
    }
    {
        BinaryTree<int> tree;
        assert(tree.getPreOrderString().empty());
    }
    {
        BinaryTree<int> tree;
        tree.Add(42);
        assert(tree.getPreOrderString() == "42 ");
    }
    {
        BinaryTree<int, std::greater<int>> tree;
        tree.Add(5);
        tree.Add(3);
        tree.Add(7);
        tree.Add(2);
        tree.Add(4);
        tree.Add(6);
        tree.Add(8);
        
        assert(tree.getPreOrderString() == "5 7 8 6 3 4 2 ");
    }
    {
        BinaryTree<int> tree;
        tree.Add(1);
        tree.Add(1);
        tree.Add(1);
        
        assert(tree.getPreOrderString() == "1 1 1 ");
    }
}


int main() {
    tests();
    solve(std::cin, std::cout);
    return 0;
}
