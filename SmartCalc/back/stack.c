#include "stack.h"

struct node *push(int new_data, struct node *top) {
  struct node *elem = malloc(sizeof(struct node));
  elem->next = top;
  elem->data = new_data;
  // top = elem;

  return elem;
}

struct node *pop(struct node *top) {
  struct node *tmp = top;
  if (top != NULL) {
    if (top->next) {
      tmp = top->next;
    } else {
      tmp = NULL;
    }
    free(top);
  }
  return tmp;
}

void destroy_stack(struct node *top) {
  while (top != NULL) {
    top = pop(top);
  }
}
