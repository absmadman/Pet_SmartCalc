#ifndef S21_POLISH_NOTATION_
#define S21_POLISH_NOTATION_
#include <math.h>

#include "stack.h"
#include "stack_for_calculations.h"
void alternate_names(const char *str, char *new_str);
double calculations(char *str);
double calc_str(const char *str);
struct number *operators(struct number *top, int sym);
struct number *make_number(char *str_number, struct number *top);
int parse_number(char *str, int *offset, char *str_number);
void to_postfix(char *str, char *result);
struct node *close_bracket(struct node *top, char *result);
struct node *push_remainder(struct node *top, char *result);
struct node *high_priority_pop(struct node *top, int new_data, char *result);
int is_digit(int sym);
int check_priority(int sym);
void append_to_str(int sym, char *result);

#endif
