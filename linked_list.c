#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node *newnode = malloc(sizeof(struct list_node));
  
  if (newnode == NULL) {
    return NULL;
  }
  
  newnode->value = value;
  newnode->next = NULL;
  return newnode; 
}

void insert_at_head(struct linked_list *list, size_t value) {
  
  struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
  new_node->value = value;
  new_node->next = list->head;
  list->head = new_node;


}

void insert_at_tail(struct linked_list *list, size_t value) {
  
  struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
  new_node->value = value;

  if (list->head == NULL) {
    list->head = new_node;
    new_node->next = NULL;
    return;
  }


  struct list_node *traverse = list->head;
  while(traverse->next != NULL){
    traverse = traverse->next;
  }
  traverse->next = new_node;
}

size_t remove_from_head(struct linked_list *list) { 
  if(list == NULL || list->head == NULL){
    return 0;
  }
  struct list_node *del = list->head;
  size_t retval = del->value;
  list->head = del->next;
  free(del);
  
return retval; 
}

size_t remove_from_tail(struct linked_list *list) { 
  
  size_t retval;
  if(list == NULL || list->head == NULL){
    return 0;
  }
  struct list_node *traverse = list->head;

  if (traverse->next == NULL) {
      retval = traverse->value;
      free(traverse);
      list->head = NULL;
      return retval;
  }

  struct list_node *travel = NULL;
  while (traverse->next != NULL) {
      travel = traverse;
      traverse = traverse->next;
  }
  retval = traverse->value;
  free(traverse);
  travel->next = NULL;
  return retval;

}

void free_list(struct linked_list list) {
  struct list_node *temp;
  struct list_node *at;

  temp = list.head;
  while(temp != NULL){
    at = temp->next;
    free(temp);
    temp = at;
  }

  list.head = NULL;
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
