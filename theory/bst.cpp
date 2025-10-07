#include <iostream>
#include <stack>
#include <queue>

template <typename T>
class BST {
protected:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Шаблонный метод для вставки элемента
    virtual Node* insert(Node* node, T val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    // Шаблонный метод для поиска элемента
    virtual Node* find(Node* node, T val) const {
        if (node == nullptr || node->data == val) {
            return node;
        }
        if (val < node->data) {
            return find(node->left, val);
        }
        return find(node->right, val);
    }

    // Шаблонный метод для удаления элемента
    virtual Node* remove(Node* node, T val) {
        if (node == nullptr) {
            return node;
        }
        if (val < node->data) {
            node->left = remove(node->left, val);
        } else if (val > node->data) {
            node->right = remove(node->right, val);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    // Шаблонный метод для нахождения минимального значения в поддереве
    virtual Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Шаблонный метод для балансировки дерева
    virtual Node* balance(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        node->left = balance(node->left);
        node->right = balance(node->right);
        return node;
    }

    // Шаблонный метод для обхода дерева (in-order)
    virtual void inOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

public:
    BST() : root(nullptr) {}

    // CRUD операции
    void insert(T val) {
        root = insert(root, val);
    }

    bool find(T val) const {
        return find(root, val) != nullptr;
    }

    void remove(T val) {
        root = remove(root, val);
    }

    void balance() {
        root = balance(root);
    }

    void inOrder() const {
        inOrder(root);
        std::cout << std::endl;
    }

    // Итератор для BST
    class Iterator {
    private:
        std::stack<Node*> stack;
        void pushLeft(Node* node) {
            while (node != nullptr) {
                stack.push(node);
                node = node->left;
            }
        }

    public:
        Iterator(Node* root) {
            pushLeft(root);
        }

        T operator*() {
            return stack.top()->data;
        }

        Iterator& operator++() {
            Node* node = stack.top();
            stack.pop();
            pushLeft(node->right);
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return !stack.empty() || !other.stack.empty();
        }
    };

    Iterator begin() {
        return Iterator(root);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

int main() {
    BST<int> bst;

    // Вставка элементов
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    // Обход дерева (in-order)
    std::cout << "In-order traversal: ";
    bst.inOrder();

    // Поиск элемента
    std::cout << "Search for 40: " << (bst.find(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 100: " << (bst.find(100) ? "Found" : "Not Found") << std::endl;

    // Удаление элемента
    std::cout << "Deleting 20\n";
    bst.remove(20);
    std::cout << "In-order traversal after deletion: ";
    bst.inOrder();

    // Балансировка дерева
    std::cout << "Balancing the tree\n";
    bst.balance();
    std::cout << "In-order traversal after balancing: ";
    bst.inOrder();

    // Использование итератора
    std::cout << "Iterating through the tree: ";
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}