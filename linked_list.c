#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
    struct list_node *node = (struct list_node *)malloc(sizeof(struct list_node));
    if (!node) return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

// Inserts a node at the head of the list
void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
    if (!new_node) return;

    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

// Inserts a node at the tail of the list
void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
    if (!new_node) return;

    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        return;
    }

    struct list_node *traverse = list->head;
    while (traverse->next != NULL) {
        traverse = traverse->next;
    }
    traverse->next = new_node;
}

// Removes and returns the value from the head
size_t remove_from_head(struct linked_list *list) {
    if (list->head == NULL) return 0;

    struct list_node *del = list->head;
    size_t retval = del->value;
    list->head = del->next;
    free(del);
    return retval;
}

// Removes and returns the value from the tail
size_t remove_from_tail(struct linked_list *list) {
    if (list->head == NULL) return 0;

    struct list_node *traverse = list->head;
    struct list_node *prev = NULL;

    while (traverse->next != NULL) {
        prev = traverse;
        traverse = traverse->next;
    }

    size_t retval = traverse->value;
    free(traverse);

    if (prev != NULL) {
        prev->next = NULL;
    } else {
        list->head = NULL;
    }

    return retval;
}

// Frees all nodes in the list
void free_list(struct linked_list *list) {
    struct list_node *temp;
    while (list->head != NULL) {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
