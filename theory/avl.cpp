#include <iostream>
#include <stack>
#include <queue>

template <typename T>
class AVLTree {
protected:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height; // Высота узла
        Node(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Вспомогательная функция для получения высоты узла
    int height(Node* node) {
        return node ? node->height : 0;
    }

    // Вспомогательная функция для обновления высоты узла
    void updateHeight(Node* node) {
        if (node) {
            node->height = std::max(height(node->left), height(node->right)) + 1;
        }
    }

    // Вспомогательная функция для получения коэффициента сбалансированности
    int balanceFactor(Node* node) {
        return node ? height(node->right) - height(node->left) : 0;
    }

    // Правый поворот
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Левый поворот
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Лево-правый поворот
    Node* leftRightRotate(Node* z) {
        z->left = leftRotate(z->left);
        return rightRotate(z);
    }

    // Право-левый поворот
    Node* rightLeftRotate(Node* z) {
        z->right = rightRotate(z->right);
        return leftRotate(z);
    }

    // Балансировка узла
    Node* balance(Node* node) {
        if (!node) return node;

        updateHeight(node);

        int bf = balanceFactor(node);

        // Левый случай
        if (bf < -1) {
            if (balanceFactor(node->left) > 0) {
                // Лево-правый случай
                return leftRightRotate(node);
            } else {
                // Правый поворот
                return rightRotate(node);
            }
        }

        // Правый случай
        if (bf > 1) {
            if (balanceFactor(node->right) < 0) {
                // Право-левый случай
                return rightLeftRotate(node);
            } else {
                // Левый поворот
                return leftRotate(node);
            }
        }

        return node;
    }

    // Вставка элемента
    Node* insert(Node* node, T val) {
        if (!node) return new Node(val);

        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        } else {
            return node; // Дубликаты не допускаются
        }

        return balance(node);
    }

    // Поиск элемента
    Node* find(Node* node, T val) const {
        if (!node || node->data == val) {
            return node;
        }
        if (val < node->data) {
            return find(node->left, val);
        }
        return find(node->right, val);
    }

    // Удаление элемента
    Node* remove(Node* node, T val) {
        if (!node) return node;

        if (val < node->data) {
            node->left = remove(node->left, val);
        } else if (val > node->data) {
            node->right = remove(node->right, val);
        } else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (!node) return node;

        return balance(node);
    }

    // Нахождение узла с минимальным значением
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    // Обход дерева (in-order)
    void inOrder(Node* node) const {
        if (!node) return;
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

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

    void inOrder() const {
        inOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree<int> avl;

    // Вставка элементов
    avl.insert(50);
    avl.insert(30);
    avl.insert(20);
    avl.insert(40);
    avl.insert(70);
    avl.insert(60);
    avl.insert(80);

    // Обход дерева (in-order)
    std::cout << "In-order traversal: ";
    avl.inOrder();

    // Поиск элемента
    std::cout << "Search for 40: " << (avl.find(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 100: " << (avl.find(100) ? "Found" : "Not Found") << std::endl;

    // Удаление элемента
    std::cout << "Deleting 20\n";
    avl.remove(20);
    std::cout << "In-order traversal after deletion: ";
    avl.inOrder();

    return 0;
}