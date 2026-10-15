#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;
struct Node
{
  int val;
  Node *left;
  Node *right;

  Node(int value)
  {
    val = value;
    left = nullptr;
    right = nullptr;
  }
};

// Queue/level-order input
Node *build_queue()
{
  int root_value;
  cin >> root_value;

  if (root_value == -1)
    return nullptr;

  Node *root = new Node(root_value);

  queue<Node *> q;
  q.push(root);

  while (!q.empty())
  {
    Node *top = q.front();
    q.pop();

    cout << "Enter the left and right value for node "
         << top->val << ": ";

    int left_value, right_value;
    cin >> left_value >> right_value;

    if (left_value != -1)
    {
      top->left = new Node(left_value);
      q.push(top->left);
    }

    if (right_value != -1)
    {
      top->right = new Node(right_value);
      q.push(top->right);
    }
  }

  return root;
}

// Recursive preorder input
Node *build_recursive()
{
  int root_value;
  cin >> root_value;

  if (root_value == -1)
    return nullptr;

  Node *root = new Node(root_value);

  root->left = build_recursive();
  root->right = build_recursive();

  return root;
}

// Parent-left-right input
Node *parent_child_input()
{
  unordered_map<int, Node *> nodes;

  int n;
  cin >> n;

  for (int i = 0; i < n; i++)
  {
    int parent_value;
    int left_value;
    int right_value;

    cin >> parent_value >> left_value >> right_value;

    if (parent_value == -1)
    {
      cout << "Invalid parent value\n";
      return nullptr;
    }

    if (nodes.find(parent_value) == nodes.end())
    {
      nodes[parent_value] = new Node(parent_value);
    }

    if (left_value != -1)
    {
      if (nodes.find(left_value) == nodes.end())
      {
        nodes[left_value] = new Node(left_value);
      }

      nodes[parent_value]->left = nodes[left_value];
    }

    if (right_value != -1)
    {
      if (nodes.find(right_value) == nodes.end())
      {
        nodes[right_value] = new Node(right_value);
      }

      nodes[parent_value]->right = nodes[right_value];
    }
  }

  cout << "Enter the node value which has to be the root: ";

  int root_value;
  cin >> root_value;

  if (root_value == -1 ||
      nodes.find(root_value) == nodes.end())
  {
    cout << "Invalid root value\n";
    return nullptr;
  }

  return nodes[root_value];
}

int main()
{
  Node *root = build_queue();

  return 0;
}