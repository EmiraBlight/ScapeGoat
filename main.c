#include <stdio.h>
#include "print.c"

int main(void) {
    struct scapeGoat *tree = createScapeGoat();
    for (int i = 0; i < 32; i++) {
        insert(tree, i);
    }
    for (int i = 32; i >16; i--) {
        deleteNode(tree, i);
    }
    deleteNode(tree, 16);
    deleteNode(tree, 15);
    deleteNode(tree, 14);
    struct node* test = flatten(tree->root);
    struct node* test2 = rebuiltTree(3,test);
    printf("flattened tree:\n");
}
