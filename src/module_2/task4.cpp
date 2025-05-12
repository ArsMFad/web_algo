#include <iostream>
#include <functional>


template <typename T, typename Compare = std::less<T>>
class AvlTree {
    struct Node {
        Node(const T& data)
            : data(data), left(nullptr), right(nullptr), height(1), count(1) {}
        
        T data;
        Node* left;
        Node* right;
        size_t height;
        size_t count;
    };

public:
    AvlTree(const Compare& comp = Compare())
        : root(nullptr), comp(comp) {}
    
    ~AvlTree() {
        destroyTree(root);
    }
    
    void Add(const T& data) {
        root = addInternal(root, data);
    }
    
    bool Has(const T& data) {
        Node* tmp = root;
        while (tmp) {
            if (!comp(tmp->data, data) && !comp(data, tmp->data))
                return true;
            else if (comp(tmp->data, data))
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return false;
    }
    
    void Delete(const T& data) {
        root = deleteInternal(root, data);
    }
    
    size_t GetPosition(const T& data) {
        return getPosition(root, data);
    }
    
    T GetByPosition(size_t position) {
        return getByPosition(root, position);
    }
    
    void DeleteByPosition(size_t position) {
        root = deleteByPosition(root, position);
    }
    
    size_t Size() const {
        return getCount(root);
    }

private:
    Node* root;
    Compare comp;
    
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    size_t getHeight(Node* node) const {
        return node ? node->height : 0;
    }
    
    size_t getCount(Node* node) const {
        return node ? node->count : 0;
    }
    
    void fixNode(Node* node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        node->count = getCount(node->left) + getCount(node->right) + 1;
    }
    
    int getBalance(Node* node) const {
        return node ? getHeight(node->right) - getHeight(node->left) : 0;
    }
    
    Node* rotateLeft(Node* node) {
        Node* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        
        fixNode(node);
        fixNode(tmp);
        
        return tmp;
    }
    
    Node* rotateRight(Node* node) {
        Node* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        
        fixNode(node);
        fixNode(tmp);
        
        return tmp;
    }
    
    Node* doBalance(Node* node) {
        fixNode(node);
        
        int balance = getBalance(node);
        if (balance == 2) {
            if (getBalance(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        } else if (balance == -2) {
            if (getBalance(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        return node;
    }
    
    Node* addInternal(Node* node, const T& data) {
        if (!node)
            return new Node(data);
        
        if (comp(node->data, data))
            node->right = addInternal(node->right, data);
        else
            node->left = addInternal(node->left, data);
        
        return doBalance(node);
    }
    
    Node* findMin(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }
    
    Node* removeMin(Node* node) {
        if (!node->left)
            return node->right;
        
        node->left = removeMin(node->left);
        return doBalance(node);
    }
    
    Node* deleteInternal(Node* node, const T& data) {
        if (!node)
            return nullptr;
        
        if (comp(node->data, data)) {
            node->right = deleteInternal(node->right, data);
        } else if (comp(data, node->data)) {
            node->left = deleteInternal(node->left, data);
        } else {
            Node* left = node->left;
            Node* right = node->right;
            
            delete node;
            
            if (!right)
                return left;
            
            Node* min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            
            return doBalance(min);
        }
        
        return doBalance(node);
    }
    
    size_t getPosition(Node* node, const T& data) {
        if (!node)
            return 0;
        
        if (comp(data, node->data))
            return getPosition(node->left, data);
        else if (comp(node->data, data))
            return getCount(node->left) + 1 + getPosition(node->right, data);
        else
            return getCount(node->left);
    }
    
    T getByPosition(Node* node, size_t position) {
        size_t leftCount = getCount(node->left);
        
        if (position < leftCount)
            return getByPosition(node->left, position);
        else if (position == leftCount)
            return node->data;
        else
            return getByPosition(node->right, position - leftCount - 1);
    }
    
    Node* deleteByPosition(Node* node, size_t position) {
        if (!node)
            return nullptr;
        
        size_t leftCount = getCount(node->left);
        
        if (position < leftCount) {
            node->left = deleteByPosition(node->left, position);
        } else if (position > leftCount) {
            node->right = deleteByPosition(node->right, position - leftCount - 1);
        } else {
            Node* left = node->left;
            Node* right = node->right;
            
            delete node;
            
            if (!right)
                return left;
            
            Node* min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            
            return doBalance(min);
        }
        
        return doBalance(node);
    }
};


void solve(std::istream &in, std::ostream &out) {
    AvlTree<int, std::greater<int>> tree;
    
    int N;
    in >> N;
    
    for (int i = 0; i < N; ++i) {
        int command, value;
        in >> command >> value;
        
        if (command == 1) {
            tree.Add(value);
            out << tree.GetPosition(value) << "\n";
        } else if (command == 2) {
            tree.DeleteByPosition(value);
        }
    }
}


int main() {
    solve(std::cin, std::cout);
    
    return 0;
}
