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

void freeScapeGoat(const struct scapeGoat* scapeGoat) {

  if (scapeGoat == NULL) {
    return;
  }

    destroyScapeGoatHelper(scapeGoat->root);

  free((void *)scapeGoat); //I...this is dumb ngl


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

  //just based it on wikipedia pseudocode

  struct node* y = NULL;
  struct node* x = tree->root;

  while (x != NULL) {
    y = x;
    if (data > x->data) {
      x = x->right;
    } else {
      x = x->left;
    }
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

struct node* getSuccessor(struct node* currNode) {
  //gets successor of node and returns pointer to it
  if (currNode == NULL || currNode->right == NULL) {
    return currNode;
  }
  currNode = currNode->right;
  while (currNode != NULL && currNode->left != NULL) {
    currNode = currNode->left;
  }
  return currNode;
}

int deleteNode(const struct scapeGoat* tree, const int data) {
  if (tree->root == NULL) { //if tree is empty it's not removed
    return -1;
  }
  struct node* parent = NULL;
  struct node* current = tree->root;

  while (current && current->data != data) {

    parent = current;

    if (current->data > data) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }

  //we are now at the node we want to delete, and we have its parent.

  if (current == NULL) {
    return -1; //not found in the tree
  }
  if (parent == NULL) {
    parent = tree->root;
  }

  if (current->left == NULL && current->right == NULL) { //simple case, deleting a leaf
    free(current);
    if (data>parent->data) {
      parent->right = NULL;
    }
    else {
      parent->left = NULL;
    }
    return 0;
  }

  if (current->left == NULL) { //one child, on the right
    struct node* temp = current->right;
    free(current);
    if (data > parent->data) {
      parent->right =temp;
    }
    else {
      parent->left = temp;
    }
    return 0;
  }


  if (current->right == NULL) { //one child, on the left
    struct node* temp = current->left;
    free(current);
    if (data > parent->data) {
      parent->right = temp;
    }
    else {
      parent->left = temp;
    }
    return 0;
  }

  //now we have the last case, two children

  if (current->right->left == NULL) { //if right child has no successor (its smallest in its subtree)
    struct node* temp = current->right;
    temp->left = current->left;
    free(current);
    if (data > parent->data) {
      parent->right = temp;
    }
    else {
      parent->left = temp;
    }
    return 0;
  }

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
  current->data = temp->data; //honestly I forgot how to do the way that actually switches the nodes...I opted for the choice
  free(temp);//that just moves the data because I remember how that works
  return 0;

}
