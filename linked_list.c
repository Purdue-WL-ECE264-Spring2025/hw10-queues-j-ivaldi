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
  while(list->head != NULL){
    traverse = traverse->next;
  }
  new_node->value = value;
  traverse->next = new_node;
  new_node->next = NULL;
  
}

size_t remove_from_head(struct linked_list *list) { 
  if(list == NULL){
    return 0;
  }
  struct list_node *del = list->head;
  size_t retval = del->value;
  list->head = del->next;
  free(del);
  
return retval; 
}

size_t remove_from_tail(struct linked_list *list) { 
  
  if(list == NULL){
    return 0;
  }

  struct list_node *traverse = list->head;
  struct list_node *trav = NULL;

  while(list->head != NULL){
    trav = traverse;
    traverse = traverse->next;
  }
  size_t retval = traverse->value;
  free(traverse);
  trav->next = NULL;
  
  
return retval; }

void free_list(struct linked_list list) {
  struct list_node *temp;
  while(temp->next != NULL){
    temp = list.head;
    list.head = list.head->next;
    free(temp);
  }


}
