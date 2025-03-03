#include <stdio.h>
#include "print.c"

int main(void) {
    struct scapeGoat *tree = createScapeGoat();
    insert(tree,10);
    insert(tree,7);
    insert(tree,15);
    insert(tree,5);
    insert(tree,8);
    insert(tree,11);
    insert(tree,18);
    struct node* test = flatten(tree->root);
    struct node* test2 = rebuildTree(5,test);
    printf("flattened tree:\n");
}
