#include "polishnotation.h"

void append_to_str(int sym, char *result) {
  //  static int counter_res = 0;
  result[strlen(result)] = sym;
  //  counter_res += 1;
}

int check_priority(int sym) {
  int priority = 0;

  if (sym == '+' || sym == '-') {
    priority = 1;
  } else if (sym == '*' || sym == '/' || sym == '%') {
    priority = 2;
  } else if (sym == '^') {
    priority = 3;
  } else if (sym == '~') {
    priority = 4;
  } else if (sym == '(') {
    priority = 0;
  } else if (sym == ')') {
    priority = 6;
  } else if (sym == 's' || sym == 'S' || sym == 'c' || sym == 'C' ||
             sym == 't' || sym == 'T' || sym == 'l' || sym == 'L' ||
             sym == 'q') {
    priority = 5;
  }
  return priority;
}

int is_digit(int sym) {
  int ret_num = 0;
  if (sym > 47 && sym < 58) {
    ret_num = 1;
  }
  return ret_num;
}

struct node *high_priority_pop(struct node *top, int new_data, char *result) {
  int priority = check_priority(new_data);
  int flag = 0;
  while (top && flag == 0) {
    if (priority <= check_priority(top->data)) {
      // append_to_str(32, result);
      append_to_str(top->data, result);
      top = pop(top);
    } else {
      flag = 1;
    }
  }
  top = push(new_data, top);
  return top;  // mb pomenat
}
struct node *high_priority_pop_for_degree(struct node *top, int new_data,
                                          char *result) {
  int priority = check_priority(new_data);
  int flag = 0;
  while (top && flag == 0) {
    if (priority < check_priority(top->data)) {
      // append_to_str(32, result);
      append_to_str(top->data, result);
      top = pop(top);
    } else {
      flag = 1;
    }
  }
  top = push(new_data, top);
  return top;  // mb pomenat
}
struct node *push_remainder(struct node *top, char *result) {
  while (top) {
    append_to_str(32, result);
    append_to_str(top->data, result);
    // top = top->next;
    top = pop(top);
  }
  return top;
}

struct node *close_bracket(struct node *top, char *result) {
  while (top->data != '(') {
    append_to_str(top->data, result);
    top = pop(top);
  }
  top = pop(top);
  return top;
}

void to_postfix(char *str, char *result) {
  struct node *top = NULL;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (is_digit(str[i]) == 1 || str[i] == 46) {
      append_to_str(str[i], result);
    } else if (str[i] == '(') {
      top = push(str[i], top);
    } else if (str[i] == ')') {
      append_to_str(32, result);
      top = close_bracket(top, result);
    } else if (str[i] == '^') {
      append_to_str(32, result);
      top = high_priority_pop_for_degree(top, str[i], result);

    } else {
      append_to_str(32, result);
      top = high_priority_pop(top, str[i], result);
    }
  }
  top = push_remainder(top, result);
  destroy_stack(top);
}

int parse_number(char *str, int *offset, char *str_number) {
  int dot = 0;
  int flag = 0;
  for (int i = *offset; flag == 0; i++) {
    if (is_digit(str[i])) {
      append_to_str(str[i], str_number);
      //      str_number[i - *offset] = str[i];
    } else if (str[i] == 46) {
      dot = 1;
      append_to_str(str[i], str_number);
      //      str_number[i - *offset] = str[i];
    } else {
      flag = 1;
      if (i > (int)strlen(str)) {
        *offset = (int)strlen(str);
      } else {
        *offset = i;
      }
    }
  }
  return dot;
}

struct number *make_number(char *str_number, struct number *top) {
  double number = 0;
  sscanf(str_number, "%lf", &number);
  top = push_num(number, top);
  return top;
}

struct number *operators(struct number *top, int sym) {
  double right = top->data;
  double result = 0;
  top = pop_num(top);
  // top = top -> next;

  if (sym == '+') {
    result = right + top->data;
    top = pop_num(top);
  } else if (sym == '-') {
    result = top->data - right;
    top = pop_num(top);
  } else if (sym == '*') {
    result = top->data * right;
    top = pop_num(top);
  } else if (sym == '/') {
    if (right != 0) {
      result = top->data / right;
      top = pop_num(top);
    } else {
      result = NAN;
    }
  } else if (sym == '~') {
    result = -right;
  } else if (sym == '^') {
    result = pow(top->data, right);
    top = pop_num(top);
  } else if (sym == 'q') {
    result = sqrt(right);
  } else if (sym == 's') {
    result = sin(right);
  } else if (sym == 'c') {
    result = cos(right);
  } else if (sym == 't') {
    result = tan(right);
  } else if (sym == 'S') {
    result = asin(right);
  } else if (sym == 'C') {
    result = acos(right);
  } else if (sym == 'T') {
    result = atan(right);
  } else if (sym == 'l') {
    result = log(right);
  } else if (sym == 'L') {
    result = log10(right);
  } else if (sym == '%') {
    result = fmod(top->data, right);
    top = pop_num(top);
  }
  top = push_num(result, top);
  return top;
}

double calculations(char *str) {
  struct number *top = NULL;
  //  top = push_num(1.0, top);

  for (int i = 0; i < (int)strlen(str); i += 1) {
    if (is_digit(str[i]) == 1) {
      char str_number[1000] = "\0";
      parse_number(str, &i, str_number);
      //      i -= 1;
      top = make_number(str_number, top);
    } else if (str[i] != 32) {
      top = operators(top, str[i]);
    }
  }
  double result = top->data;
  destroy_stack_num(top);
  return result;
}

void alternate_names(const char *str, char *new_str) {
  for (int i = 0, j = 0; i < (int)strlen(str); i++) {
    if (str[i] == '-' && str[i - 1] == '(') {
      new_str[j] = '~';
    } else {
      new_str[j] = str[i];
    }
    j += 1;
  }
}

double calc_str(const char *str) {
  char result[1000] = "\0";
  char new_str[1000] = "\0";
  alternate_names(str, new_str);
  to_postfix(new_str, result);
  double res = 0;
  res = calculations(result);
  return res;
}
