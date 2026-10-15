#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int value) {
        val = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* insertNode(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->val) {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->val) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

// Returns the smallest node in a subtree
Node* findMinimum(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }

    return root;
}

Node* deleteNode(Node* root, int value) { 
    // Value not found
    if (root == nullptr) {
        return nullptr;
    }

    // Search in the left subtree
    if (value < root->val) {
        root->left = deleteNode(root->left, value);
    }

    // Search in the right subtree
    else if (value > root->val) {
        root->right = deleteNode(root->right, value);
    }

    // Node found
    else {
        // Case 1: Node has no children
        if (root->left == nullptr &&
            root->right == nullptr) {
            
            delete root;
            return nullptr;
        }

        // Case 2A: Node has only a right child
        if (root->left == nullptr) {
            Node* child = root->right;

            delete root;
            return child;
        }

        // Case 2B: Node has only a left child
        if (root->right == nullptr) {
            Node* child = root->left;

            delete root;
            return child;
        }

        // Case 3: Node has two children
        Node* successor = findMinimum(root->right);

        // Copy successor's value into current node
        root->val = successor->val;

        // Delete the original successor node
        root->right =
            deleteNode(root->right, successor->val);
    }

    return root;
}

void inorder(Node* root) {
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter node values: ";

    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;

        root = insertNode(root, value);
    }

    int valueToDelete;
    cout << "Enter value to delete: ";
    cin >> valueToDelete;

    root = deleteNode(root, valueToDelete);

    cout << "Tree after deletion: ";
    inorder(root);

    cout << endl;

    return 0;
}