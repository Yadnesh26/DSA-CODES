#include<iostream>
using namespace std;

class node {
public:
    int data;
    node *lptr;
    node *rptr;
};

class BST {
public:
    node* create_root(int key) {
        node* root = new node;
        root->data = key;
        root->lptr = NULL;
        root->rptr = NULL;
        return root;
    }

    void insert(int key, node* root) {
        if (key < root->data) {
            if (root->lptr == NULL) {
                node* newnode = new node;
                newnode->data = key;
                newnode->lptr = NULL;
                newnode->rptr = NULL;
                root->lptr = newnode;
            } else {
                insert(key, root->lptr);
            }
        } else if (key > root->data) {
            if (root->rptr == NULL) {
                node* newnode = new node;
                newnode->data = key;
                newnode->lptr = NULL;
                newnode->rptr = NULL;
                root->rptr = newnode;
            } else {
                insert(key, root->rptr);
            }
        } else {
            cout << "Duplicate data not allowed" << endl;
        }
    }

    void search(int key, node* root) {
        if (root == NULL) {
            cout << "Search Not Found!!!!" << endl;
            return;
        }

        if (key == root->data) {
            cout << "Search Found!!!!" << endl;
        } else if (key < root->data) {
            search(key, root->lptr);
        } else {
            search(key, root->rptr);
        }
    }

    void inorder(node* root) {
        if (root != NULL) {
            inorder(root->lptr);
            cout << root->data << " ";
            inorder(root->rptr);
        }
    }

    void preorder(node* root) {
        if (root != NULL) {
            cout << root->data << " ";
            preorder(root->lptr);
            preorder(root->rptr);
        }
    }

    void postorder(node* root) {
        if (root != NULL) {
            postorder(root->lptr);
            postorder(root->rptr);
            cout << root->data << " ";
        }
    }

    void descorder(node* root) {
        if (root != NULL) {
            descorder(root->rptr);
            cout << root->data << " ";
            descorder(root->lptr);
        }
    }

    void find_min(node* root) {
        if (root == NULL) {
            cout << "Tree is empty." << endl;
            return;
        }

        while (root->lptr != NULL) {
            root = root->lptr;
        }
        cout << "Minimum Value is " << root->data << endl;
    }

    void swap_nodes(node* root) {
        if (root == NULL) return;

        node* temp = root->lptr;
        root->lptr = root->rptr;
        root->rptr = temp;

        swap_nodes(root->lptr);
        swap_nodes(root->rptr);
    }

    int long_path(node* root) {
        if (root == NULL) return 0;

        int left = long_path(root->lptr);
        int right = long_path(root->rptr);

        return max(left, right) + 1;
    }
};

int main() {
    node* root = NULL;
    BST bst;
    int choice;
    int key, skey;

    while (1) {
        cout << "\nEnter your Choice" << endl;
        cout << "1) Insert" << endl;
        cout << "2) Search" << endl;
        cout << "3) Inorder" << endl;
        cout << "4) Preorder" << endl;
        cout << "5) Postorder" << endl;
        cout << "6) Descending Order" << endl;
        cout << "7) Find minimum value" << endl;
        cout << "8) Swap nodes" << endl;
        cout << "9) Longest path" << endl;
        cout << "10) Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the Number to be added in BST" << endl;
                cin >> key;
                if (root == NULL) {
                    root = bst.create_root(key);
                } else {
                    bst.insert(key, root);
                }
                break;

            case 2:
                if (root == NULL) {
                    cout << "Tree is empty!" << endl;
                    break;
                }
                cout << "Enter the Number to be searched in BST" << endl;
                cin >> skey;
                bst.search(skey, root);
                break;

            case 3:
                bst.inorder(root);
                cout << endl;
                break;

            case 4:
                bst.preorder(root);
                cout << endl;
                break;

            case 5:
                bst.postorder(root);
                cout << endl;
                break;

            case 6:
                bst.descorder(root);
                cout << endl;
                break;

            case 7:
                bst.find_min(root);
                break;

            case 8:
                bst.swap_nodes(root);
                cout << "Nodes swapped successfully." << endl;
                break;

            case 9:
                cout << "Longest Path is " << bst.long_path(root) << endl;
                break;

            case 10:
                exit(0);

            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
