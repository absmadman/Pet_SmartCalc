#include "credit_back.h"

#include <math.h>
#include <stdio.h>

double monthly(double loan, double rate, double period) {
  double rate_for_month = rate / (100 * 12);
  double delim = 1 - (pow(1 + rate_for_month, -period));
  double payment = loan * (rate_for_month / delim);
  return payment;
}

double total(double loan, double rate, double period) {
  return (monthly(loan, rate, period) * period);
}

double overpayment(double loan, double rate, double period) {
  return (total(loan, rate, period) - loan);
}

double monthy_anu(double loan, double rate, double period) {
  return total(loan, rate, period) / period;
}

double monthy_diff(double loan, double rate, double period) {
  double sd = loan / period;
  double sp = (loan * (rate / 100) * 30.46) / 365;
  return sd + sp;
}

double total_diff(double loan, double rate, double period) {
  double month;
  double mon = loan / period;
  double result = 0;
  for (int i = period; i > 0; i -= 1) {
    month = monthy_diff(loan, rate, i);
    result += month;
    loan -= mon;
  }
  return result;
}
double overpayment_diff(double loan, double rate, double period) {
  return total_diff(loan, rate, period) - loan;
  // return (total_diff(loan, rate, period) - loan);
}
