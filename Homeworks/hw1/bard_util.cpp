#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bard_util.h"

Node :: Node(){
    word = NULL;
    freq = 0;
    next = NULL;
}

Node :: Node(char* new_word){
    word = new_word;
    freq = 1;
    next = NULL;
}

LinkedList :: LinkedList(){
	head = NULL;
}

void LinkedList :: update(char* temp){
  if(!head){
    char* new_entry = strdup(temp);
    Node* new_node = new Node(new_entry);
    head = new_node;
    return;
  }
  if(!strcmp(head->word,temp)){
    head->freq++;
    return;
  }
  Node* curr = head;
  Node* prev = NULL;
  Node* curr_freq_head = curr;
  Node* last_freq_head = NULL;
  Node* prev_curr_freq_head = NULL;
  while(curr){
    if(curr->freq < curr_freq_head->freq){  //new frequency
      prev_curr_freq_head = prev;
      last_freq_head = curr_freq_head;
      curr_freq_head = curr;
    }
    if(!strcmp(curr->word, temp)){ //word found
      curr->freq++;
      if(!last_freq_head){  //no larger freq in front
        prev->next = curr->next;
        curr->next = head;
        head = curr;
        return;
      }
      if(last_freq_head->freq > curr->freq){
        prev->next = curr->next;
        curr->next = prev_curr_freq_head->next;
        prev_curr_freq_head->next = curr;
        return;
      }
      if(prev->freq > curr->freq){  //prev still has larger freq
        return;
      }
      Node* after_me = find_after_me(last_freq_head, temp);
      if(after_me){ //not head of freq
        prev->next = curr->next;
        curr->next = after_me->next;
        after_me->next = curr;
        return;
      }else{  //new head of this freq
        prev->next = curr->next;
        if(last_freq_head == head){ 
          curr->next = head;
          head = curr;
          return;
        }
        curr->next = last_freq_head->next;
        last_freq_head->next = curr;
        swap(last_freq_head, curr);   
        return;      
      }
    }
    //not this word, check next
    prev = curr;
    curr = curr->next;
  }
  //if reached here, temp is a new word
  char* new_entry = strdup(temp);
  Node* new_node = new Node(new_entry);
  Node* after_me = find_after_me(curr_freq_head, temp);
  if(after_me){
    new_node->next = after_me->next;
    after_me->next = new_node;
    return;
  }else{  //head of 1 freq
    if(!prev_curr_freq_head){
      new_node->next = head;
      head = new_node;
      return;
    }
    new_node->next = curr_freq_head->next;
    curr_freq_head->next = new_node;
    swap(curr_freq_head, new_node);   
    return;   
  }
}

void swap(Node* node_one, Node* curr){
    char* word_buffer = node_one->word;
    int freq_buffer = node_one->freq;
    node_one->word = curr->word;
    node_one->freq = curr->freq;
    curr->word = word_buffer;
    curr->freq = freq_buffer;
}


Node* find_after_me(Node* this_head, char* new_word){
  Node* curr = this_head;
  Node* prev = NULL;
  while(curr && (curr->freq==this_head->freq) && strcmp(curr->word, new_word) < 0 ){
    prev = curr;
    curr = curr->next;
  }
  return prev;
}

Node* LinkedList :: find_word(int rank){
  if(rank < 0){
    return NULL;
  }
  Node* curr = head;
  int index = 0;
  while(curr){
    if(index == rank){
      return curr;
    }
    curr = curr->next;
    index++;
  }
  return NULL;
}

void LinkedList :: deleteList(){
  Node* curr = head;
  while(curr){
    Node* delete_me = curr;
    curr = curr->next;
    free(delete_me->word);
    delete(delete_me);
  }
}