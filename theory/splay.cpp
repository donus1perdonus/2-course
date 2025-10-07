#include <iostream>
#include <stack>
#include <queue>

template <typename T>
class SplayTree {
protected:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Вспомогательная функция для выполнения операции splay
    Node* splay(Node* node, T val) {
        if (node == nullptr || node->data == val) {
            return node;
        }

        if (val < node->data) {
            if (node->left == nullptr) {
                return node;
            }
            // Zig-Zig (левый-левый)
            if (val < node->left->data) {
                node->left->left = splay(node->left->left, val);
                node = rotateRight(node);
            }
            // Zig-Zag (левый-правый)
            else if (val > node->left->data) {
                node->left->right = splay(node->left->right, val);
                if (node->left->right != nullptr) {
                    node->left = rotateLeft(node->left);
                }
            }
            return (node->left == nullptr) ? node : rotateRight(node);
        } else {
            if (node->right == nullptr) {
                return node;
            }
            // Zag-Zag (правый-правый)
            if (val > node->right->data) {
                node->right->right = splay(node->right->right, val);
                node = rotateLeft(node);
            }
            // Zag-Zig (правый-левый)
            else if (val < node->right->data) {
                node->right->left = splay(node->right->left, val);
                if (node->right->left != nullptr) {
                    node->right = rotateRight(node->right);
                }
            }
            return (node->right == nullptr) ? node : rotateLeft(node);
        }
    }

    // Правый поворот (Zig)
    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    // Левый поворот (Zag)
    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    // Вставка элемента с последующим splay
    Node* insert(Node* node, T val) {
        if (node == nullptr) {
            return new Node(val);
        }
        node = splay(node, val);
        if (node->data == val) {
            return node; // Элемент уже существует
        }
        Node* newNode = new Node(val);
        if (val < node->data) {
            newNode->right = node;
            newNode->left = node->left;
            node->left = nullptr;
        } else {
            newNode->left = node;
            newNode->right = node->right;
            node->right = nullptr;
        }
        return newNode;
    }

    // Поиск элемента с последующим splay
    Node* find(Node* node, T val) {
        if (node == nullptr) {
            return nullptr;
        }
        node = splay(node, val);
        return (node->data == val) ? node : nullptr;
    }

    // Удаление элемента с последующим splay
    Node* remove(Node* node, T val) {
        if (node == nullptr) {
            return nullptr;
        }
        node = splay(node, val);
        if (node->data != val) {
            return node; // Элемент не найден
        }
        Node* temp;
        if (node->left == nullptr) {
            temp = node->right;
        } else {
            temp = splay(node->left, val);
            temp->right = node->right;
        }
        delete node;
        return temp;
    }

    // Обход дерева (in-order)
    void inOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

public:
    SplayTree() : root(nullptr) {}

    // Вставка элемента
    void insert(T val) {
        root = insert(root, val);
    }

    // Поиск элемента
    bool find(T val) {
        root = splay(root, val);
        return (root != nullptr && root->data == val);
    }

    // Удаление элемента
    void remove(T val) {
        root = remove(root, val);
    }

    // Обход дерева (in-order)
    void inOrder() const {
        inOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    SplayTree<int> splayTree;

    // Вставка элементов
    splayTree.insert(50);
    splayTree.insert(30);
    splayTree.insert(20);
    splayTree.insert(40);
    splayTree.insert(70);
    splayTree.insert(60);
    splayTree.insert(80);

    // Обход дерева (in-order)
    std::cout << "In-order traversal: ";
    splayTree.inOrder();

    // Поиск элемента
    std::cout << "Search for 40: " << (splayTree.find(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 100: " << (splayTree.find(100) ? "Found" : "Not Found") << std::endl;

    // Удаление элемента
    std::cout << "Deleting 20\n";
    splayTree.remove(20);
    std::cout << "In-order traversal after deletion: ";
    splayTree.inOrder();

    return 0;
}