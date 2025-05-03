#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

class avlnode {
public:
    std::string keyword;
    std::string meaning;
    avlnode *left, *right;
    int height;

    avlnode(const std::string &k, const std::string &m) 
        : keyword(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class dictionary {
private:
    avlnode *root;

    int getHeight(avlnode *node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(avlnode *node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    avlnode *rightRotate(avlnode *y) {
        avlnode *x = y->left;
        avlnode *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    avlnode *leftRotate(avlnode *x) {
        avlnode *y = x->right;
        avlnode *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    avlnode *insert(avlnode *node, const std::string &key, const std::string &meaning) {
        if (!node) return new avlnode(key, meaning);

        if (key < node->keyword)
            node->left = insert(node->left, key, meaning);
        else if (key > node->keyword)
            node->right = insert(node->right, key, meaning);
        else {
            std::cout << "Keyword already exists.\n";
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->keyword)
            return rightRotate(node);
        if (balance < -1 && key > node->right->keyword)
            return leftRotate(node);
        if (balance > 1 && key > node->left->keyword) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->keyword) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    avlnode *minValueNode(avlnode *node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    avlnode *deleteNode(avlnode *node, const std::string &key) {
        if (!node) return node;

        if (key < node->keyword)
            node->left = deleteNode(node->left, key);
        else if (key > node->keyword)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left || !node->right) {
                avlnode *temp = node->left ? node->left : node->right;

                if (!temp) {
                    delete node;
                    return nullptr;
                } else {
                    avlnode *old = node;
                    node = temp;
                    delete old;
                }
            } else {
                avlnode *temp = minValueNode(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = deleteNode(node->right, temp->keyword);
            }
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(avlnode *node) {
        if (node) {
            inorder(node->left);
            std::cout << node->keyword << ": " << node->meaning << "\n";
            inorder(node->right);
        }
    }

    void descending(avlnode *node) {
        if (node) {
            descending(node->right);
            std::cout << node->keyword << ": " << node->meaning << "\n";
            descending(node->left);
        }
    }

    avlnode *search(avlnode *node, const std::string &key) {
        if (!node || node->keyword == key) return node;
        if (key < node->keyword) return search(node->left, key);
        return search(node->right, key);
    }

    void deleteAll(avlnode *node) {
        if (node) {
            deleteAll(node->left);
            deleteAll(node->right);
            delete node;
        }
    }

public:
    dictionary() : root(nullptr) {}
    ~dictionary() { deleteAll(root); }

    void insert(const std::string &key, const std::string &meaning) {
        root = insert(root, key, meaning);
    }

    void deleteKey(const std::string &key) {
        root = deleteNode(root, key);
    }

    void update(const std::string &key, const std::string &newMeaning) {
        avlnode *node = search(root, key);
        if (node)
            node->meaning = newMeaning;
        else
            std::cout << "Keyword not found.\n";
    }

    void displayAscending() {
        inorder(root);
    }

    void displayDescending() {
        descending(root);
    }

    void searchWord(const std::string &key) {
        avlnode *node = search(root, key);
        if (node)
            std::cout << "Found: " << node->keyword << " -> " << node->meaning << "\n";
        else
            std::cout << "Not found.\n";
    }
};

int main() {
    dictionary dict;
    int choice;
    std::string key, meaning;

    do {
        std::cout << "\n1. Insert\n2. Update\n3. Delete\n4. Display Ascending\n5. Display Descending\n6. Search\n7. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Enter keyword: ";
                std::getline(std::cin, key);
                std::cout << "Enter meaning: ";
                std::getline(std::cin, meaning);
                dict.insert(key, meaning);
                break;
            case 2:
                std::cout << "Enter keyword to update: ";
                std::getline(std::cin, key);
                std::cout << "Enter new meaning: ";
                std::getline(std::cin, meaning);
                dict.update(key, meaning);
                break;
            case 3:
                std::cout << "Enter keyword to delete: ";
                std::getline(std::cin, key);
                dict.deleteKey(key);
                break;
            case 4:
                std::cout << "Dictionary (Ascending Order):\n";
                dict.displayAscending();
                break;
            case 5:
                std::cout << "Dictionary (Descending Order):\n";
                dict.displayDescending();
                break;
            case 6:
                std::cout << "Enter keyword to search: ";
                std::getline(std::cin, key);
                dict.searchWord(key);
                break;
            case 7:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
