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
    inorder(tree);
    printf("\nSearch for 15: %p\n",(void*)search(tree,15));
    deleteNode(tree,15);
    printf("Search for 15: %p\n",(void*)search(tree,15));
    inorder(tree);
    freeScapeGoat(tree);
}
