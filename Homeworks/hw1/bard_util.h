#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
using namespace std;

class Node {
  public:
    char *word;
    int freq;
    Node *next;
    Node();
    Node(char*);
};

class LinkedList{
  public:
		Node *head; // Stores head of linked list
		LinkedList(); // Default constructor sets head to null
    Node* find_word(int);
		void deleteList(); 
    void update(char*);
};
void swap(Node*, Node*);
Node* find_after_me(Node*, char*);
