#include <iostream>
#include "bst.h"
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

int main(int argc, char** argv){
    if (argc < 3){
        throw std :: invalid_argument(
            "Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>");
    }
    ifstream input;
    ofstream output;
    input.open(argv[1]);
    output.open(argv[2]);
    string line;
    char *cmd, *op, *str1, *str2;

    BST bst; //initialization

    while(getline(input, line)){
        if(line.length() == 0){
            continue;
        }
        cmd = strdup(line.c_str());
        op = strtok(cmd, " \t");
        str1 = strtok(NULL, " \t");
        string s1(str1);

        if(strcmp(op,"i") == 0){    //insert
            bst.insert(s1);
        }
        if(strcmp(op,"r") == 0){  //countNodes
            str2 = strtok(NULL, " \t");
            string s2(str2);
            output << bst.countNodes(s1, s2) << endl;
        }
        // else if(strcmp(op,"p") == 0){  //print in PreOrder
        //     string temp = bst.printPreOrder();
        //     cout << "printing" << endl << temp << endl;
        // }
        free(cmd);
    }
    //free mem?
    input.close();
    output.close();
} 