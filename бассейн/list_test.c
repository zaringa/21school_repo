#include "list.h"

void test_add_door() {
    struct door* d1 = (struct door*)malloc(sizeof(struct door));
    d1->id = 1;
    struct node* root = init(d1);

    struct door* d2 = (struct door*)malloc(sizeof(struct door));
    d2->id = 2;

    add_door(root, d2);
    if (root->next && root->next->door->id == 2) {
        printf("test_add_door: 1   2  SUCCESS\n");
    } else {
        printf("test_add_door: FAIL\n");
    }

    destroy(root);
}

void test_remove_door() {
    struct door* d1 = (struct door*)malloc(sizeof(struct door));
    d1->id = 1;

    struct door* d2 = (struct door*)malloc(sizeof(struct door));
    d2->id = 2;

    struct node* root = init(d1);
    add_door(root, d2);

    root = remove_door(root->next, root);
    if (!root->next) {
        printf("test_remove_door: 1 1  SUCCESS\n");
    } else {
        printf("test_remove_door: FAIL\n");
    }

    destroy(root);
}

int main() {
    test_add_door();
    test_remove_door();
    return 0;
}