#include "stack_for_calculations.h"

struct number *push_num(double new_data, struct number *top) {
  struct number *elem = malloc(sizeof(struct number));
  elem->next = top;
  elem->data = new_data;
  // top = elem;

  return elem;
}

struct number *pop_num(struct number *top) {
  struct number *tmp = top;
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

void destroy_stack_num(struct number *top) {
  while (top != NULL) {
    top = pop_num(top);
  }
}
