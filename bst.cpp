#include<iostream>
#include <vector>
using namespace std;

#include "bst.h"

Tnode * BST::rightRotation(Tnode *cur) { //cout << "right" << endl; 
  Tnode *leftChild = cur->left;
  cur->left = cur->left->right;
  updateHeight(cur);
  leftChild->right = cur;
  updateHeight(leftChild);
  return leftChild;
} 

Tnode * BST::leftRotation(Tnode *cur) { //cout << "left" << endl;
  Tnode *rightChild = cur->right;
  cur->right = cur->right->left;
  updateHeight(cur);
  rightChild->left = cur;
  updateHeight(rightChild);
  return rightChild;
}

int BST::balanceFactor(Tnode *cur) {
  int bf =  getHeight(cur->left) - getHeight(cur->right);
  //cout << bf << endl;
  return bf;
} 

void BST::printBF(Tnode *cur) { 
   if (cur == NULL)
   return;
   
   printBF(cur->left);
   cout << balanceFactor(cur) << " ";
   printBF(cur->right);
}

void BST::updateSize(Tnode *cur) { 
  cur->size = 1 + getSize(cur->left) + getSize(cur->right);
}   
int BST::getSize(Tnode* cur) { 
  if (!cur) 
    return 0;
  else
    return 1 + getSize(cur->left) + getSize(cur->right);
}
 
void BST::printSize(Tnode *cur) { 
  if (cur == NULL) {
    return;
  } 
  printSize(cur->left);
  cout << getSize(cur) << " ";
  printSize(cur->right);
} 

void BST::print_inorder(Tnode *cur){
  if (cur == NULL)
    return;
  
  print_inorder(cur->left);
  cout << "(" << cur->key << ")" << "{";
  
  for (int i = 0; i < cur->value.size(); i++) { 
    cout << cur->value[i] << " ";
  } cout << "} ";
  
  print_inorder(cur->right);
}//print_inorder

void BST::findPrint(Tnode* cur, string akey) {
  if (cur == NULL) 
    return;
  
  if (cur->key == akey) { 
    for (int i = 0; i < cur->value.size(); i++) { 
      cout << cur->value[i] << " ";
    } cout << endl;
    return;
  } 
  findPrint(cur->left, akey);
  findPrint(cur->right, akey);

} 

int BST::getHeight(Tnode *cur) { 
  if (!cur) 
    return -1;

  return cur->height;
} 

void BST::heightPrint(Tnode *cur) { 
  if (cur == NULL) 
    return;
  
  heightPrint(cur->left);  
  cout << getHeight(cur) << " ";
  heightPrint(cur->right);
  
} 

void BST::clean(Tnode *cur){
  if(cur == NULL)
    return;
  clean(cur->left);
  clean(cur->right);
  delete cur;
}//clean()

void BST::updateHeight(Tnode *cur) {
  if (cur->left == NULL && cur->right == NULL) {
    cur->height = 0;
    return;
  }
  else if (cur->left == NULL && cur->right != NULL) {
    cur->height = cur->right->height + 1;
    return;
  }
  else if (cur->left != NULL && cur->right == NULL) {
    cur->height = cur->left->height + 1;
    return;
  } 
  cur->height = (max(cur->left->height, cur->right->height) + 1);

} 
  
Tnode* BST::insert(Tnode* cur, string akey, string word){
     int bf = 0; 
     if (cur->key == akey) { 
        cur->value.push_back(word);
        return cur;
      }  
      
      if (akey < cur->key) {
        if (cur->left == NULL){
          cur->left = new Tnode(akey, word);
        } else { 
          cur->left = insert (cur->left, akey, word);
          bf = balanceFactor(cur);
          if (bf > 1) { //cout << "first case" << endl;
            if (getHeight(cur->left->left) >= getHeight(cur->left->right)){ 
              cur = rightRotation(cur);
            } else { 
              cur->left = leftRotation(cur->left);
              cur = rightRotation(cur);
            }
          }
          else if (bf < -1) { //cout << "second case" << endl;
            if (getHeight(cur->right->right) >= getHeight(cur->right->left)) { 
              cur = leftRotation(cur);
            } else { //inside case
              cur->right = rightRotation(cur->right);
              cur = leftRotation(cur);
            }
          }
        } 
      }//if 
      else if (akey > cur->key) {
        if (cur->right == NULL) {
          cur->right = new Tnode(akey, word);
        } else { 
          cur->right = insert (cur->right, akey, word);
          bf = balanceFactor(cur);
          if (bf > 1) { //cout << "third case" << endl;
            if (getHeight(cur->left->left) >= getHeight(cur->left->right)){
              cur = rightRotation(cur);
            } else {
              cur->left = leftRotation(cur->left);
              cur = rightRotation(cur);
            }
          } 
          else if (bf < -1) { //cout << "fourth case" << endl;
            if (getHeight(cur->right->right) >= getHeight(cur->right->left)) {
              cur = leftRotation(cur);
            } else { //inside case
              cur->right = rightRotation(cur->right);
              cur = leftRotation(cur);
            } 
          }
        }
      } //else if
  
  updateHeight(cur);
  updateSize(cur); 
  return cur;
}//insert()


Tnode* BST::remove(Tnode *cur, string ak) { 
  if (!cur)
    return NULL;
  if (ak < cur->key) { 
    cur->left = remove(cur->left, ak);
    return restore_balance(cur);
  } 
  else if (ak > cur->key) { 
    cur->right = remove(cur->right, ak);
    return restore_balance(cur);
  } 
  else if (ak == cur->key) { //found the node
    if (cur->left == NULL) { 
      Tnode *R = cur->right;
      delete cur;
      return R;
    }
    else if (cur->right == NULL) { 
      Tnode *L = cur->left;
      delete cur;
      return L;
    } else { //two children 
      Tnode *leftmost = getLeftmost(cur->right);
      cur->key = leftmost->key;
      cur->value = leftmost->value;
      cur->right = remove(cur->right, leftmost->key);
      return restore_balance(cur);
    }
    }      
  return cur;
}  

Tnode* BST::getLeftmost(Tnode *cur) { 
  if (cur) { 
    if(cur->left) 
      return getLeftmost(cur->left);
    else 
      return cur;
    } 
  return NULL;
} 
 
Tnode *BST::restore_balance(Tnode *cur) {
  int bf = balanceFactor(cur);
  if (bf > 1) { //cout << "third case" << endl;
    if (getHeight(cur->left->left) >= getHeight(cur->left->right)){
      cur = rightRotation(cur);
     } else {
       cur->left = leftRotation(cur->left);
       cur = rightRotation(cur);
     }
  }
  else if (bf < -1) { //cout << "fourth case" << endl;
    if (getHeight(cur->right->right) >= getHeight(cur->right->left)) {
      cur = leftRotation(cur);
    } else { //inside case
      cur->right = rightRotation(cur->right);
      cur = leftRotation(cur);
    } 
  }
  updateHeight(cur);
  updateSize(cur);
  return cur;
}

string BST::findLCA(Tnode *cur, string key1, string key2) { 
  if (!cur) 
    return "";
  vector<string> v1;
  vector<string> v2;
  collectPath(cur, v1, key1);
  collectPath(cur, v2, key2);
  int i = 0;
  int j = 0;
  while (i < v1.size() && j < v2.size()) { 
    if (v1[i] == v2[j]) { 
      i++; j++;
    } else { 
      break;
    } 
  } 
  return v1[--i];
}
  
void BST::collectPath(Tnode *cur, vector<string> &v, string key) { 
  if (!cur) 
    return;

  v.push_back(cur->key);
  if (key < cur->key && cur->left != NULL) {
    collectPath(cur->left, v, key);
  } 
  else if (key > cur->key && cur->right != NULL) { 
    collectPath(cur->right, v, key);
  } 
  else {//equal
    v.push_back(cur->key);
    return;
  } 
}

Tnode* BST::findNode(Tnode *cur, string key) { 
  if (!cur)  
    return NULL;

  if (cur->key < key) { 
    return findNode(cur->right, key);
  }
  else if (cur->key > key) { 
    return findNode(cur->left, key);
  } else
    return cur;

return NULL;
} 
   
void BST::collectSubtree(Tnode *cur, vector <string> &v) { 
  if (!cur) 
    return;
  
  collectSubtree(cur->left, v);
  v.push_back(cur->key);
  collectSubtree(cur->right, v);

} 

void BST::findKthSmallest(Tnode *cur, int kthSmallest) { 
  if (!cur) 
    cout << " ";
  
  if (kthSmallest == getSize(cur->left) + 1) { 
    cout << cur->key;
  } 
  else if (kthSmallest <= getSize(cur->left)) { 
    findKthSmallest(cur->left, kthSmallest);
  } else
    findKthSmallest(cur->right, kthSmallest - getSize(cur->left) - 1);

}

void BST::printLongestPath(Tnode *cur) { 
  if (!cur) 
    return;
 
  cout << cur->key << " ";
  if (getHeight(cur->left) > getHeight(cur->right)) { 
    //cout << getHeight(cur->left) << " > " << getHeight(cur->right) << " going L " << endl;
    printLongestPath(cur->left);
  } 
  else if (getHeight(cur->right) > getHeight(cur->left)) { 
    //cout << getHeight(cur->right) << " > " << getHeight(cur->left) << " going R " << endl;
    printLongestPath(cur->right);
  } else  
    printLongestPath(cur->left);
} 

 
