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
    int minDepthCall(Node* node) const;
    
public:
    BinaryTree();
    ~BinaryTree();
    
    BinaryTree(const BinaryTree& other) = delete;
    
    void insert(int value);
    int minDepth() const;
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

int BinaryTree::minDepthCall(Node* node) const {
    if (!node) return 0;

    if (!node->left && !node->right) return 1;
    
    if (!node->left) return 1 + minDepthCall(node->right);
    if (!node->right) return 1 + minDepthCall(node->left);
    
    return 1 + std::min(minDepthCall(node->left), minDepthCall(node->right));
}

int BinaryTree::minDepth() const {
    return minDepthCall(root);
}


void solve(std::istream& in, std::ostream& out) {
    BinaryTree bin_tree;
    int value;
    
    while (in >> value) {
        bin_tree.insert(value);
    }
    
    out << bin_tree.minDepth() << "\n";
}


int main() {
    solve(std::cin, std::cout);
    
    return 0;
}
