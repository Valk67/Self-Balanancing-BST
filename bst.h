#include<iostream>
using namespace std;
#include "tnode.h"
#ifndef BST_H
#define BST_H


class BST{
  public:
    BST():  root(NULL) {};
    ~BST(){ clean(root); root = NULL;}
    void insert(string akey, string word){
      if(root == NULL){
        root = new Tnode(akey, word);
        return;
      }else
       root = insert(root, akey, word);
    }
    void printBF() {return printBF(root);}
    void remove(string ak) {
      if (!root) 
        return;
      else { 
      root = remove(root, ak);
      }
    }
    void printSize() {return printSize(root);}
    void heightPrint() {return heightPrint(root);}
    void print_inorder(){print_inorder(root);  cout << endl;}
    void findPrint(string akey) {findPrint(root, akey);}
    string findLCA(string key1, string key2) {return findLCA(root, key1, key2);}
    void collectSubtree(vector<string> &v, string key) {
      Tnode *tmp = findNode(root, key);
      collectSubtree(tmp, v);
    } 
    void findKthSmallest(int kthSmallest) {findKthSmallest(root, kthSmallest);} 
    void printLongestPath() {return printLongestPath(root);}
  private:
    Tnode *root = NULL;
    Tnode *leftRotation(Tnode *cur);
    Tnode *rightRotation(Tnode *cur);
    void printBF(Tnode *cur);
    void printSize(Tnode *cur);
    int getSize(Tnode *cur);
    void updateSize(Tnode *cur);
    void print_inorder(Tnode *cur);
    void updateHeight(Tnode *cur);
    void findPrint(Tnode* cur, string akey);
    int getHeight(Tnode *cur);
    int balanceFactor(Tnode *cur);
    void clean(Tnode* cur);
    void heightPrint(Tnode *cur);
    Tnode* insert(Tnode* cur, string akey, string word);
    Tnode* remove(Tnode *cur, string ak);
    Tnode* getLeftmost(Tnode *cur);
    Tnode* restore_balance(Tnode *cur);
    string findLCA(Tnode *cur, string key1, string key2);
    void collectPath(Tnode *cur, vector<string> &v, string key);
    Tnode* findNode(Tnode *cur, string key);
    void collectSubtree(Tnode *cur, vector<string> &v);
    void findKthSmallest(Tnode *cur, int kthSmallest);
    void printLongestPath(Tnode *cur);
};


#endif

