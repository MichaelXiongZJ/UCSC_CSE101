#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fstream>
#include "bard_util.h"

int get_max_len(string filename){
  ifstream input;
  input.open(filename);
  string line;
  int max = 0;
  while(getline(input, line)){
    int temp = line.length();
    if(temp > max){
      max = temp;
    }
  }
  input.close();
  return max;
}


void load_file(string filename, LinkedList arr[]){
  ifstream input;
  string line;
  int index;
  input.open(filename);
  while(getline(input, line)){
    if(line.length() == 0){
      continue;
    }
    char *temp = strdup(line.c_str());
    index = line.length() - 5;
    arr[index].update(temp);
    free(temp);
  }
  input.close();
}


int main(int argc, char **argv){
  clock_t start, end;
  start = clock();
  if (argc != 3){
    throw std::invalid_argument("Usage: ./bard <INPUT FILE> <OUTPUT FILE>");
  }
  int max_len = get_max_len("shakespeare-cleaned5.txt");
  LinkedList LLArray[max_len - 4];
  load_file("shakespeare-cleaned5.txt", LLArray);

  //i/o setup
  ifstream input;
  ofstream output;
  input.open(argv[1]);
  output.open(argv[2]);
  //read each line of command
  string line;
  int length;
  int rank;
  char *temp;
  while(getline(input, line)){
    if(line.length() == 0){
      continue;
    }
    temp = strdup(line.c_str());
    length = stoi(strtok(temp, " \t"));
    rank = stoi(strtok(NULL, " \t"));
    free(temp);
    //find and write
    if(length > max_len || length < 5){
      output << "-\n";
    }else{
      Node *target = LLArray[length-5].find_word(rank);
      if(target){
        output << target->word;
      }else{
        output << "-";
      }
      output <<"\n";
    }
  }
  input.close();
  output.close();

  //debug: print out all the LinkedLists
  // ofstream output;
  // output.open(argv[2]);
  // int index = 0;
  // while(index < max_len - 4){
  //   Node* curr = LLArray[index].head;
  //   while(curr){
  //     output << curr->word;
  //     output << ", ";
  //     output << curr->freq;
  //     output << "\n";
  //     curr = curr->next;
  //   }
  //   output <<"\n";
  //   index++;
  // }
  // output.close();

  // free memory
  int k = max_len - 4;
  for(int i = 0; i < k; i++){
    LLArray[i].deleteList();
  }

  //time calculation
  end = clock();
  double time_taken = (end - start) / (double)CLOCKS_PER_SEC;
  printf("Overall took: %f seconds.\n", time_taken);

  return 0;
}