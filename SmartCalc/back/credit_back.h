#ifndef S21_SMART_CALC_CREDIT_
#define S21_SMART_CALC_CREDIT_

double monthly(double loan, double rate, double period);
double total(double loan, double rate, double period);
double overpayment(double loan, double rate, double period);
double monthy_diff(double loan, double rate, double period);
double total_diff(double loan, double rate, double period);
double overpayment_diff(double loan, double rate, double period);
double monthy_anu(double loan, double rate, double period);
#endif
