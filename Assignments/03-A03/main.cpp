#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class Bst {
    Node* root;

    void _print(Node* subroot) {
        if (!subroot) {
            return;
        }
        _print(subroot->left);
        cout << subroot->data << " ";
        _print(subroot->right);
    }

    void _insert(Node*& subroot, int x) {
        if (!subroot) { // if(subroot == nullptr)
            subroot = new Node(x);
        }
        else {
            if (x < subroot->data) {
                _insert(subroot->left, x);
            }
            else {
                _insert(subroot->right, x);
            }
        }
    }

    Node* _delete(Node*& subroot, int x)
    {
        if (!subroot) {
            return subroot; // If the node doesn't exist, return null
        }
        else if (subroot->data == x) {
            cout << "Deleting node " << subroot->data << endl;  // Debugging output
            if (subroot->left == nullptr) {
                Node* temp = subroot->right;
                delete subroot;
                return temp;
            }
            else if (subroot->right == nullptr) {
                Node* temp = subroot->left;
                delete subroot;
                return temp;
            }
            else {
                // Node with two children: get the inorder successor (smallest in the right subtree)
                Node* temp = findMin(subroot->right);
                cout << "Inorder successor: " << temp->data << endl;  // Debugging output
                subroot->data = temp->data;  // Copy the inorder successor's data to this node
                subroot->right = _delete(subroot->right, temp->data);  // Delete the inorder successor
                return subroot;
            }
        }
        else {
            if (x < subroot->data) {
                subroot->left = _delete(subroot->left, x);  // Correct recursive call
            }
            else {
                subroot->right = _delete(subroot->right, x); // Correct recursive call
            }
        }
        return subroot; // Return the root of the modified subtree
    }

    Node* findMin(Node* root) {
        while (root && root->left) {
            root = root->left;
        }
        return root;
    }

public:
    Bst() { root = nullptr; }
    void insert(int x) { _insert(root, x); }
    void delete_(int x) { root = _delete(root, x); } // Update the root after deletion
    void print() { _print(root); }
};

int main() {
    Bst tree;
    tree.insert(6);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);
    tree.insert(11);
    tree.insert(13);
    tree.insert(12);
    tree.insert(14);
    tree.insert(5);
    tree.insert(7);
    tree.insert(17);

    // Print the tree before deletion
    cout << "Tree before deletion: ";
    tree.print();
    cout << endl;

    // Delete 13
    tree.delete_(11);

    // Print the tree after deletion
    cout << "Tree after deletion: ";
    tree.print();
    cout << endl;

    return 0;
}
