#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *parent;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

Node *findInorderSuccessor(Node *node)
{
    if (node == nullptr)
        return nullptr;

    // Case 1: Right subtree exists.
    // Successor is its leftmost node.
    if (node->right != nullptr)
    {
        Node *current = node->right;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    // Case 2: No right subtree.
    // Move upward until node is a left child.
    Node *current = node;
    Node *ancestor = node->parent;

    while (ancestor != nullptr &&
           current == ancestor->right)
    {
        current = ancestor;
        ancestor = ancestor->parent;
    }

    return ancestor;
}


void connectLeft(Node *parent, Node *child)
{
    parent->left = child;

    if (child != nullptr)
        child->parent = parent;
}

void connectRight(Node *parent, Node *child)
{
    parent->right = child;

    if (child != nullptr)
        child->parent = parent;
}

int main()
{
    /*
              20
             /  \
           10    30
          /  \
         5   15
    */

    Node *root = new Node(20);
    Node *node10 = new Node(10);
    Node *node30 = new Node(30);
    Node *node5 = new Node(5);
    Node *node15 = new Node(15);

    connectLeft(root, node10);
    connectRight(root, node30);
    connectLeft(node10, node5);
    connectRight(node10, node15);

    Node *successor = findInorderSuccessor(node15);

    if (successor != nullptr)
        cout << "Inorder successor: " << successor->data << '\n';
    else
        cout << "No inorder successor exists\n";

    return 0;
}