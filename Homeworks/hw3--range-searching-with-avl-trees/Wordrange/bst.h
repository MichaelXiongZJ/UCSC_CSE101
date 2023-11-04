#ifndef BST_H
#define BST_H

#include <string>

using namespace std;

class Node{
	public:
        int height, subTreeSize;
        string key;
        Node *left, *right;
        Node(string str){
            key = str;
            height = 1;
            subTreeSize = 1;
            left = right = NULL;
        }
};

class BST{
    private:
        Node *root;
    public:
        BST();
        void insert(string);
        Node* insert(Node*, string);
        Node* leftRotate(Node*);
        Node* rightRotate(Node*);
        int countNodes(string, string);
        // int countNodes(Node*, string, string);
        int getBalance(Node*);
        void updateSubTreeSize(Node*);
        int getSubTreeSize(Node*);
        void updateHeight(Node*);
        int getHeight(Node*);
        string printPreOrder();
        string printPreOrder(Node*);

        int rangeSearch(string, string);
};

#endif