#include <iostream>
#include <stack>
#include <fstream>
#include <array>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
using namespace std;

//helper
void copy_array(int* target, int* ref, int size){
  for(int i = 0; i < size; i++){
    target[i] = ref[i];
  }
}

//check if a board is valid
bool isValid(int* board, int size, int col, int row){
  for(int i = 0; i < size; i++){
    if(i == col){
      continue;
    }
    if(board[i] == row){
      return false;
    }
    int diff = abs(i - col);
    int nono = row - diff;
    if(nono >= 0 && nono < size){
      if(board[i] == nono){
        return false;
      }
    }
    nono = row + diff;
    if(nono >= 0 && nono < size){
      if(board[i] == nono){
        return false;
      }
    }
  }
  return true;
}

//mimic recursive with stack, find a complete board
int* find(int* init, int size){
  for(int i = 0; i < size; i++){
    if(init[i] != -1){
      if(!isValid(init, size, i, init[i])){
        return NULL;
      }
    }
  }
  int *result, *stackTop;
  stack<int*> recurStack;
  recurStack.push(init);
  while(!recurStack.empty()){
    stackTop = recurStack.top();
    recurStack.pop();
    int empty_col = -1;
    int i = 0;
    while(i < size && empty_col == -1){
      if(stackTop[i] == -1){
        empty_col = i;
      }
      i++;
    }
    if(empty_col == -1){
      result = stackTop;
      while(!recurStack.empty()){
        int* temp = recurStack.top();
        recurStack.pop();
        free(temp);
      }
      return result;
    }
    // for(int i = 0; i < size; i++){ //both correct
    for(int i = size-1; i >= 0; i--){
      int *temp = new int[size];
      copy_array(temp, stackTop, size);
      temp[empty_col] = i;
      if(isValid(temp, size, empty_col, i)){
        recurStack.push(temp);
      }else{
        delete [] temp;
      }
    }
  }
  return NULL;
}

int main(int argc, char **argv){
  if (argc != 3){
    throw std::invalid_argument("Usage: ./nqueens <INPUT FILE> <OUTPUT FILE>");
  }
  ifstream input;
  ofstream output;
  input.open(argv[1]);
  output.open(argv[2]);
  string line;
  char *temp;
  char *word;
  while(getline(input, line)){
    if(line.length() == 0){
      continue;
    }
    temp = strdup(line.c_str());
    word = strtok(temp, " ");
    int size = stoi(word);
    // int new_board[size];
    int *new_board = new int[size];
    for(int i = 0; i < size; i++){
      new_board[i] = -1;
    }
    int row, col;
    bool failed_already = false;
    while(word){
      col = -1;
      row = -1;
      word = strtok(NULL, " ");
      if(word){
        col = stoi(word);
        word = strtok(NULL, " ");
          if(word){
          row = stoi(word);
          if(new_board[col-1] != -1){
            failed_already = true;
          }
          if(row >= 0 && col >= 0){
            new_board[col-1] = row-1;
          }else{
            failed_already = true;
          }
        }
      }
    }
    free(temp);
    if(!failed_already){
      int* result = find(new_board, size);
      if(result){
        for(int i = 0; i < size; i++){
          output << i+1 << " " << result[i]+1 << " ";
        }
        delete [] result;
      }else{
        output << "No solution";
      }
      output << "\n";
    }else{
      output << "No solution\n";
    }
  }
  input.close();
  output.close();
  return 0;
}