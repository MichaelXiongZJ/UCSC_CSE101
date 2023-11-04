#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

BST :: BST(){
	root = NULL;
}


void BST :: insert(string str){
    if(!root){
        Node *to_insert = new Node(str);
        root = to_insert;
    }
    else{
        root = insert(root, str);
    }
}

Node* BST :: insert(Node* start, string key){
    if(key < start->key){    //go left
        if(start->left == NULL){
            Node *to_insert = new Node(key);
            start->left = to_insert;
        }
        else{    //recursive call
            start->left = insert(start->left, key);
        }
    }else if(key > start->key){   //go right
        if(start->right == NULL){
            Node *to_insert = new Node(key);
            start->right = to_insert;
        }
        else{    //recursive call
            start->right = insert(start->right, key);
        }
    }else{   //already exist
        return start;
    }
    updateHeight(start);
    updateSubTreeSize(start);
    int balanceFactor = getBalance(start);
    if (balanceFactor > 1 && key < start->left->key){
        return rightRotate(start); 
    }else if (balanceFactor < -1 && key > start->right->key){
        return leftRotate(start);
    }else if (balanceFactor > 1 && key > start->left->key){
        start->left = leftRotate(start->left);
        return rightRotate(start);
    }else if (balanceFactor < -1 && key < start->right->key){
        start->right = rightRotate(start->right);
        return leftRotate(start);
    }else{
        return start;
    }
}


Node* BST :: leftRotate(Node* x){
    Node* replacement = x->right;
    Node* grandChild = replacement->left;
    replacement->left = x;
    x->right = grandChild;
    updateHeight(x);
    updateHeight(replacement);
    updateSubTreeSize(x);
    updateSubTreeSize(replacement);
    return replacement;
}

Node* BST :: rightRotate(Node* x){
    Node* replacement = x->left;
    Node* grandChild = replacement->right;
    replacement->right = x;
    x->left = grandChild;
    updateHeight(x);
    updateHeight(replacement);
    updateSubTreeSize(x);
    updateSubTreeSize(replacement);
    return replacement;
}

//get number of nodes between two strings
//log(n) time
//use node->subTreeSize to get number of nodes in a subtree
int BST :: countNodes(string start, string end){
    Node* curr = root;
    int count = 0;
    while(curr){
        if(curr->key >= start && curr->key <= end){
            count += getSubTreeSize(curr->left) + 1;
            curr = curr->right;
        }else if(curr->key < start){
            curr = curr->right;
        }else{
            curr = curr->left;
        }
    }
    return count;
}

int BST :: getBalance(Node* node){
    if(!node){
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}


void BST :: updateSubTreeSize(Node* node){
    node->subTreeSize = 1 + getSubTreeSize(node->left)
                         + getSubTreeSize(node->right);
}

int BST :: getSubTreeSize(Node* node){
    if(!node){
        return 0;
    }
    return node->subTreeSize;
}


void BST :: updateHeight(Node* node){
    node->height = 1 + max(getHeight(node->left), 
                        getHeight(node->right));
}

int BST :: getHeight(Node* node){
    if(!node){
        return 0;
    }
    return node->height;
}


//example from prof. shesh
string BST :: printPreOrder(){
    return printPreOrder(root);
}

string BST :: printPreOrder(Node* start){
    if(start == NULL) // base case
        return ""; // return empty string
    string leftpart = printPreOrder(start->left);
    string rightpart = printPreOrder(start->right);
    string output = start->key;
    if(leftpart.length() != 0) // left part is empty
        output = output + " " + leftpart; // append left part
    if(rightpart.length() != 0) // right part in empty
        output = output + " " + rightpart; // append right part
    return output;
}