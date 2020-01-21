#include<iostream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include<stdio.h>
#include<cstdio>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<vector>
using namespace std;

#include "bst.h"

int main(){
  BST Tree;
  string command;
  string key;
  string word;
  int prefix = 0;
  while (cin >> command) {

    if (command == "insert") {
      cin >> word;
      cin >> prefix;
      key = word.substr(0, prefix);
      Tree.insert(key, word);
    }
    else if (command == "print_inorder") {
      Tree.print_inorder();
      cout << '\n';
    }
    else if (command == "heightPrint") {
      Tree.heightPrint();
      cout << '\n' << '\n';
    }
    else if (command == "printSize") {
      Tree.printSize();
      cout << '\n' << '\n';
    }
    else if (command == "printBF") {
      Tree.printBF();
      cout << '\n' << '\n';
    }
    else if (command == "findPrint") {
      cin >> key;
      Tree.findPrint(key);
    }
    else if (command == "remove") {
      string key2;
      cin >> key2;
      Tree.remove(key2);
    }
    else if (command == "findLCA") {
      string one;
      string two;
      cin >> one;
      cin >> two;
      string answer = Tree.findLCA(one, two);
      cout << answer << endl;
    }
    else if (command == "findKthSmallest") {
      int kth;
      cin >> kth;
      Tree.findKthSmallest(kth);
      cout << '\n';
    }
    else if (command == "collectSubtree") {
      vector<string> v;
      cin >> key;
      Tree.collectSubtree(v, key);
      for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
      }
      cout << '\n';
    }
    else if (command == "printLongestPath") {
      Tree.printLongestPath();
      cout << '\n';
    }
    else
    cout << "invalid command" << endl;
    }
return 0;
}
