#include<iostream>

using namespace std;

struct Node{
  int val;
  Node* left;
  Node* right;
  Node* parent;

  Node(int value){
    val=value;
    left=nullptr;
    right=nullptr;
    parent=nullptr;
  }
};

Node* find_successor(Node *root){
  

  if(root->right){  
    root=root->right;
    while(root->left!=nullptr){
      root=root->left;
     }
     return root;
  }
  else{
    //there is no node below the root node so look in parent 
    Node* ancestor=root->parent;
    while(ancestor && ancestor->right==root){
      root=ancestor;
      ancestor=root->parent;
    }
    return ancestor;
  }

}


Node* delete_node(Node* root,int target){

  //first find the node to be deleted , like first reach there 

  if(root->val>target){
    root->left=delete_node(root->left);
  }

  else if(root->val<target){
    root->right=delete_node(root->right,target);
  }

  else{
    //we found the target node
    //no child
    if(!root->left && !root->right){
      delete(root);
      return nullptr;
    }
    if(root->left && root->right){
      Node* successor=find_successor(root);
      root->val=successor->val;
      return delete_node(root->right,successor->val);
    }
    //1 child (left child)
    if(root->left){
      Node* par=root->parent;
      if(par!=nullptr && par->left=root){
        par->left=root->left;
        delete root;
      }
    }
    //1child (right child )
    //2 child

  }



}

int main(){

  int n;
  cin>>n;

  Tree *root=new Tree();
  
  return 0;
}