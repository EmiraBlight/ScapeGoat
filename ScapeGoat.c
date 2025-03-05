//
// Created by emira on 2/28/25.
//




#include "ScapeGoat.h"
#define LOG32(n) (log(n) / log(3.0/2.0))

struct scapeGoat * createScapeGoat(void){

  //creates a new tree and returns pointer to it

    struct scapeGoat* newTree = (struct scapeGoat*) malloc(sizeof(struct scapeGoat));

    if(newTree == NULL){
      return NULL;
    }

    newTree->root = NULL;
    newTree->n = 0;
    newTree->q = 0;

    return newTree;

  }

void destroyScapeGoatHelper(struct node *node) {
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

  }
  else if (data < y->data) {
    y->left = newNode;

  }
  else {
    y->right = newNode;

  }

  tree->n++;
  tree->q++;
  index--;
  stack[index] = newNode;
  //add scape goat logic


  if (index >LOG32(tree->q) && tree->n >2) {
    int sizeOfNode =  size(stack[index]);
    int sizeOfParent = ceil(size(stack[index-1]));
    while ((float)sizeOfNode <= ceil((sizeOfParent*0.6666666))) {
    index--;
      sizeOfNode =  sizeOfParent;
      sizeOfParent = size(stack[index-1]);
    }
    struct node* newTree;

    if (index >0){
    newTree =  rebuiltTree(size(stack[index-1]),stack[index-1]);
    }

    if (index <= 0) { // recreating from root
      tree->root = rebuiltTree(size(tree->root),tree->root);
      tree->q = tree->n;
      return 0;
    }

    else {
      if (newTree->data > stack[index-2]->data) {
        stack[index-2]->right = newTree;
      }
      else {
        stack[index-2]->left = newTree;
      }
    }

    tree->q = tree->n;

  }

  return 0;

}


int deleteNode(struct scapeGoat* tree, const int data) {
  if (tree->root == NULL) { //if tree is empty it's not removed
    return -1;
  }




  struct node* parent =  NULL;
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
  if (parent == NULL) { //removing head
    struct node * toBeDeleted = tree->root;

     if (tree->root->left == NULL && tree->root->right == NULL) { //no kids
       free(toBeDeleted);
       tree->root = NULL;
     }

    else if (tree->root->left == NULL) {
      tree->root = tree->root->right;
      free(toBeDeleted);
    }
    else if (tree->root->right == NULL) {
      tree->root =tree->root->left;
      free(toBeDeleted);
    }
    else { //two kids

      struct node *scanner = tree->root->right;
      struct node *parentOfSuccessor = NULL;

      while (scanner->left != NULL) {
        parentOfSuccessor = scanner;
        scanner = scanner->left;
      }

      tree->root->data = scanner->data;

      if (parentOfSuccessor != NULL) {
        parentOfSuccessor->left = scanner->right;
      } else {
        tree->root->right = scanner->right;
      }

      free(scanner); //copy paste it like the non head version
      tree->n --;




      }

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

  tree->n--;


  if (tree->n<(tree->q/2)) {

    tree->root = rebuiltTree(tree->n,tree->root);
    tree->q = tree->n;
  }


  return 0;


}


int size(const struct node* root){

  if (root == NULL) {
    return 0;
  }

  return 1 + size(root->left) + size(root->right);

}


struct node* flattenHelper(struct node* x,struct node* y) {

  if (x==NULL) {
    return y;
  }

  x->right = flattenHelper(x->right,y);
  return flattenHelper(x->left,x);

}

struct node* flatten(struct node* tree) {
  if (tree == NULL) {
    return NULL;
  }
  tree = flattenHelper(tree,NULL);
  struct node* result = tree;
  while (result &&result->right != NULL) {
    result->left = NULL;
    result = result->right;
  }
  return tree;
}

struct node* rebuildTreeHelper(const int n,struct node* x) {

  if (x == NULL) {
    return NULL;
  }

  if (n==0) {
      x->left = NULL;
    return x;
  }

  struct node* r = rebuildTreeHelper(ceil((n-1)/2.0),x);


    struct node* s = rebuildTreeHelper(floor((n-1)/2),r->right);


      r->right = s->left;
      s->left = r;


  return s;

}

struct node* rebuiltTree(const int n, struct node* scapeGoat) {

  struct node* w = createNode(INT_MAX);
  struct node* z = flattenHelper(scapeGoat,w);
  rebuildTreeHelper(n,z);

  return w->left;
}

void inOrderHelper(const struct node* n) {

  if (n != NULL) {
    inOrderHelper(n->left);
    printf("%d ", n->data);
    inOrderHelper(n->right);
  }

}



void inorder(const struct scapeGoat* tree) {
  if (tree == NULL) {
    return;
  }
  inOrderHelper(tree->root);
  printf("\n");
}

void preOderHelper(const struct node* n) {
  if (n != NULL) {
    printf("%d ", n->data);
    inOrderHelper(n->left);
    inOrderHelper(n->right);
  }
}


void preorder(const struct scapeGoat* tree) {
  preOderHelper(tree->root);
  printf("\n");
}

void postorderHelper(const struct node* n) {
  if (n != NULL) {
    postorderHelper(n->left);
    postorderHelper(n->right);
    printf("%d ", n->data);
  }
}

void postorder(const struct scapeGoat* n) {
  postorderHelper(n->root);
  printf("\n");
}
