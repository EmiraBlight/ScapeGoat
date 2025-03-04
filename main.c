#include <stdio.h>
#include "print.c"

int main(void) {
    struct scapeGoat* tree = createScapeGoat();

    char first;
    int second;
    char third;
    while (1) {
        scanf(" %c", &first);
        if (first == 'q') {
            freeScapeGoat(tree);
            return 0;
        }

        if (first == 'e') {
            destroyScapeGoatHelper(tree->root);
        }
        if (first == 't') {
            scanf(" %c", &third);
        }
        else {
            scanf("%d", &second);
        }
        if (first == 'i') {
            insert(tree, second);
        }
        if (first == 'd') {
            deleteNode(tree, second);
        }
        if (first == 's') {
            const struct node* found = search(tree, second);
            if (found) {
                printf("%d is present", second);
            }
            else{
                printf("%d is missing", second);
            }
        }

        if (first == 't') {
            if (third == 'i') {
                inorder(tree);
            }
            else if (third == 'l') {
                preorder(tree);
            }
            else if (third == 'r') {
                postorder(tree);
            }
        }


    }
}
