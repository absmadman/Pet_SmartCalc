#ifndef S21_STACK_CALC_
#define S21_STACK_CALC_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct number {
  double data;
  struct number *next;
};

struct number *push_num(double new_data, struct number *top);
struct number *pop_num(struct number *top);
void destroy_stack_num(struct number *top);

#endif
