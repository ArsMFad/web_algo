#include <iostream>
#include <queue>


struct Node {
    int value;
    Node* left;
    Node* right;
    
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};


class BinaryTree {
private:
    Node* root;
    
    void clearTree(Node* node);
    bool allValuesEqual(Node* node, int value) const;
    
public:
    BinaryTree();
    ~BinaryTree();
    
    BinaryTree(const BinaryTree& other) = delete;
    
    void insert(int value);
    bool areAllValuesEqual() const;
};

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    clearTree(root);
}

void BinaryTree::clearTree(Node* node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

bool BinaryTree::allValuesEqual(Node* node, int value) const {
    if (!node) return true;
    if (node->value != value) return false;
    return allValuesEqual(node->left, value) && allValuesEqual(node->right, value);
}

void BinaryTree::insert(int value) {
    Node** current = &root;
    while (*current) {
        if (value <= (*current)->value) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    *current = new Node(value);
}

bool BinaryTree::areAllValuesEqual() const {
    if (!root) return true;
    int rootValue = root->value;
    return allValuesEqual(root, rootValue);
}


void solve(std::istream& in, std::ostream& out) {
    BinaryTree bin_tree;
    int value;
    
    while (in >> value) {
        bin_tree.insert(value);
    }
    
    out << (bin_tree.areAllValuesEqual() ? 1 : 0) << "\n";
}


int main() {
    solve(std::cin, std::cout);
    
    return 0;
}
