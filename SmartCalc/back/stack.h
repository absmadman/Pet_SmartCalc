#ifndef S21_STACK_
#define S21_STACK_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int data;
  struct node *next;
};

struct node *push(int new_data, struct node *top);
struct node *pop(struct node *top);
void destroy_stack(struct node *top);

#endif
