#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct node* init(struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return NULL;

    new_node->door = door;
    new_node->next = NULL;

    return new_node;
}

struct node* add_door(struct node* elem, struct door* door) {
    if (!elem) return NULL;

    struct node* new_node = init(door);
    if (!new_node) return NULL;

    new_node->next = elem->next;
    elem->next = new_node;

    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current != NULL) {
        if (current->door->id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (!elem || !root) return root;

    if (root == elem) {
        struct node* next = root->next;
        free(root->door);
        free(root);
        return next;
    }

    struct node* current = root;
    while (current->next && current->next != elem) {
        current = current->next;
    }

    if (current->next == elem) {
        struct node* to_remove = current->next;
        current->next = to_remove->next;
        free(to_remove->door);
        free(to_remove);
    }
    return root;
}

void destroy(struct node* root) {
    struct node* current = root;
    struct node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->door);
        free(current);
        current = next;
    }
}
