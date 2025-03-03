//
// Created by emira on 2/28/25.
//
#include <stdio.h>
#include "print.h"
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
