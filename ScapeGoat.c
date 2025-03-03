//
// Created by emira on 2/28/25.
//


#include "ScapeGoat.h"
#include <stdlib.h>

struct scapeGoat * createScapeGoat(void){

  //creates a new tree and returns pointer to it

    struct scapeGoat* newTree = (struct scapeGoat*) malloc(sizeof(struct scapeGoat));

    if(newTree == NULL){
      return NULL;
    }

    newTree->root = NULL;
    newTree->n = 1;
    newTree->q = 2;

    return newTree;

  }

void destroyScapeGoatHelper(struct node* node) {
  if(node == NULL) {
    return;
  }
  destroyScapeGoatHelper(node->left);
  destroyScapeGoatHelper(node->right);
  free(node);
}

struct scapeGoat* freeScapeGoat(const struct scapeGoat* scapeGoat) {

  //frees the whole tree and returns NULL
  if (scapeGoat == NULL) {
    return NULL;
  }

    destroyScapeGoatHelper(scapeGoat->root);


  free((void *)scapeGoat); //...this is dumb ngl
  return NULL;
}

struct node* search(const struct scapeGoat* tree, const int data) {
  struct node* current = tree->root;
  while(current != NULL) {
    if(current->data == data) {
      return current;
    }
    else if(current->data > data) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }
  return NULL;
}

struct node* createNode(int data){

  //creates a node and returns pointer to it

  struct node* newNode = (struct node*) malloc(sizeof(struct node));
  if(newNode == NULL){
    return NULL;
  }

  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;

}

int insert(struct scapeGoat* tree, const int data) {

  //insert a new node into tree. returns non 0 if fails, returns 0 if it worked

  if (tree == NULL) {
    return 1;
  }

  struct node* newNode = createNode(data);

  if(newNode == NULL) {
    free(newNode);
    return -1;
  }

  struct node *stack[64]; //64 nodes deep is far more than what I think I will need

  for(int i = 0; i < 64; i++) {
    stack[i] = NULL;
  }

  int index = 0;
  stack[0] = tree->root;
  index++;


  struct node* y = NULL;
  struct node* x = tree->root;



  while (x != NULL) {
    y = x;
    if (data > x->data) {
      x = x->right;
    } else {
      x = x->left;
    }
    stack[index] = x;
    index++;
  }
  if (y == NULL) {
    tree->root = newNode;
    return 0;
  }
  if (data < y->data) {
    y->left = newNode;
    return 0;
  }

  y->right = newNode;

  return 0;

}


int deleteNode(const struct scapeGoat* tree, const int data) {
  if (tree->root == NULL) { //if tree is empty it's not removed
    return -1;
  }

  struct node* stack[64];
  int index = 0;
  for (int i = 0; i < 64; i++) {
    stack[i] = NULL;
  }



  struct node* parent = NULL;
  struct node* current = tree->root;
  stack[0] = tree->root;
  index++;


  while (current && current->data != data) {

    parent = current;

    if (current->data > data) {
      current = current->left;
    }
    else {
      current = current->right;
    }
    stack[index] = current;
    index++;
  }

  //we are now at the node we want to delete, and we have its parent.

  if (current == NULL) {
    return -1; //not found in the tree
  }
  if (parent == NULL) {
    parent = tree->root;
  }

  else if (current->left == NULL && current->right == NULL) { //simple case, deleting a leaf
    free(current);
    if (data>parent->data) {
      parent->right = NULL;
    }
    else {
      parent->left = NULL;
    }

  }

  else if (current->left == NULL) { //one child, on the right
    struct node* temp = current->right;
    free(current);
    if (data > parent->data) {
      parent->right =temp;
    }
    else {
      parent->left = temp;
    }

  }


  else if (current->right == NULL) { //one child, on the left
    struct node* temp = current->left;
    free(current);
    if (data > parent->data) {
      parent->right = temp;
    }
    else {
      parent->left = temp;
    }
  }

  //now we have the last case, two children

  else if (current->right->left == NULL ) { //if right child has no successor (its smallest in its subtree)
    struct node* temp = current->right;
    temp->left = current->left;
    free(current);
    if (data > parent->data) {
      parent->right = temp;
    }
    else {
      parent->left = temp;
    }

  }
  else {
    struct node* p = NULL;
    struct node* temp = current->right;
    while (temp->left != NULL) {
      p = temp;
      temp = temp->left;
    }

    if (p!=NULL) {
      p->left = temp->right;
    }
    else {
      current->right = temp->right;
    }
    current->data = temp->data; //honestly I forgot how to do the way that actually switches the nodes for two child and successor...I opted for the
    free(temp);//version that just moves the data because I remember how that works
  }


 //scapegoat logic

  return 0;


}


int size(const struct node* root){

  if (root == NULL) {
    return 0;
  }

  return 1 + size(root->left) + size(root->right);

}

