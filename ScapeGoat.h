//
// Created by emira on 2/28/25.
//

#ifndef SCAPEGOAT_H

#define SCAPEGOAT_H



struct scapeGoat {

  struct node *root;
  int n;
  int q;

};


struct node{

  int data;
  struct node* left;
  struct node* right;

  };


struct scapeGoat * createScapeGoat(void);
void freeScapeGoat(const struct scapeGoat *scapeGoat);
struct node* createNode(int data);

struct node* search(const struct scapeGoat* tree, int data);

int insert(struct scapeGoat* tree, int data);
int deleteNode(const struct scapeGoat* tree, int data);


#endif //SCAPEGOAT_H
