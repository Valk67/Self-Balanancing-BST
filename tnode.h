#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef TNODE_H
#define TNODE_H


class Tnode{
  public:
  Tnode(): left(NULL), right(NULL) {};
  Tnode(string akey, string word){ 
    key = akey;
    value.push_back(word);
    left = NULL;
    right = NULL;
    height = 0;
    size = 1;
  } 
  int size;
  string key;
  vector<string>value;
  Tnode* left;
  Tnode* right;
  int height;      
};

#endif
