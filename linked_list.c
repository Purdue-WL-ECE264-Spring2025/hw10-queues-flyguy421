#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {

  // new malloc address is a "struct list_node"
    // value is value
    // points to null
  // return new malloc address

  struct list_node * node = malloc(sizeof(struct list_node));
  if (node == NULL) {
    return NULL;
  }

  node->value = value;
  node->next = NULL;
  
  return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
  // hold past head address
  // create new node
  // set list head address to new node's address
  // set new head node next to past head address

  struct list_node * past_head = list->head;
  struct list_node * node = new_node(value);
  node->next = past_head;
  list->head = node;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  // create new node
  // find last node in current list
  // point last node to new node

  struct list_node * node = new_node(value);

  if (list->head == NULL) {
    list->head = node;
    return;
  }

  struct list_node * last = list->head;
  while (last->next) {
    last = last->next;
  }
  last->next = node;
}

size_t remove_from_head(struct linked_list *list) {
  // record current head address
  // set new head address to second node
  // delete node at recorded address
  // return deleted node's value

  if (list->head == NULL) {
    return 0;
  }
  
  struct list_node * past_head = list->head;
  list->head = list->head->next;
  size_t value = past_head->value;
  free(past_head);
  return value;
}

size_t remove_from_tail(struct linked_list *list) {
  // record address of last node
  // set second to last node next to null
  // delete node at recorded address
  // return deleted node's value

  if (list->head == NULL) {
    return 0;
  }

  if (list->head->next == NULL) {
    size_t value = list->head->value;
    free(list->head);
    list->head = NULL;
    return value;
  }

  struct list_node * last = list->head;
  while (last->next) {
    last = last->next;
  }
  struct list_node * second_last = list->head;
  while (second_last->next != last) {
    second_last = second_last->next;
  }
  second_last->next = NULL;
  size_t value = last->value;
  free(last);
  return value;
}

void free_list(struct linked_list list) {
  // start at head
  // while current node isn't null
    // record next address
    // free node
    // move to next node

    struct list_node * current = list.head;
    struct list_node * next = NULL;
    while (current) {
      next = current->next;
      free (current);
      current = next;
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
