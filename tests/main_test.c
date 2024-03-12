#include "main_test.h"

START_TEST(s21_test_0) {
  double x = 0;
  double orig = 10;

  char str[255] = "5+5";
  x = calc_str(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_1) {
  double x = 0;
  double orig = 162;
  // int error = 0;

  char str[255] = "4*5*2*2*2+2";
  x = calc_str(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_2) {
  double x = 0;
  double orig = 20;
  // int error = 0;

  char str[255] = "150/10+5*2/2";
  x = calc_str(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_3) {
  double x = 0;
  double orig = 9;
  // int error = 0;

  char str[255] = "5+5-2*3/6";
  x = calc_str(str);
  ck_assert_double_eq(x, orig);
}
END_TEST
START_TEST(calc_test) {
  {
    char src[100] = "123+0.456";
    double result = calc_str(src);
    double real_result = 123.456;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-3 failed");
  }
  {
    char src[100] = "(-(-1))";
    double result = calc_str(src);
    double real_result = 1;
    ck_assert_msg(result == real_result, "test-5 failed");
  }
  {
    char src[100] = "c(10%2.2)";
    double result = calc_str(src);
    double real_result = 0.362358;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-6 failed");
  }
  {
    char src[100] = "q(l(10))";
    double result = calc_str(src);
    double real_result = 1.517427;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-7 failed");
  }
  {
    char src[100] = "T(10)+s(10)";
    double result = calc_str(src);
    double real_result = 1.644775;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-8 failed");
  }
  {
    char src[100] = "S(1)";
    double result = calc_str(src);
    double real_result = 1.570796;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-9 failed");
  }
  {
    char src[100] = "10-20*(-10)";
    double result = calc_str(src);
    double real_result = -210;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001,
                  "test-10 failed");
  }
  {
    double loan = 100000;
    double rate = 15;
    double period = 12;
    double montly = monthly(loan, rate, period);
    double tota = total(loan, rate, period);
    double overpay = overpayment(loan, rate, period);
    ck_assert_double_eq_tol(montly, 9025.831235, 1e-6);
    ck_assert_double_eq_tol(tota, 108309.974814, 1e-6);
    ck_assert_double_eq_tol(overpay, 8309.974814, 1e-6);
  }
  {
    double loan = 100000;
    double rate = 15;
    double period = 12;
    double montly = monthy_diff(loan, rate, period);
    double tota = total_diff(loan, rate, period);
    double overpay = overpayment_diff(loan, rate, period);
    ck_assert_double_eq_tol(montly, 9585.114155, 1e-6);
    ck_assert_double_eq_tol(tota, 108136.575342, 1e-6);
    ck_assert_double_eq_tol(overpay, 8136.575342, 1e-6);
  }
  {
    char src[100] = "2^2^3";
    double result = calc_str(src);
    double real_result = 256;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001,
                  "test-10 failed");
  }
}
END_TEST

Suite *calc_str_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("S21_SMART_CALC");

  tc = tcase_create("Core");

  tcase_add_test(tc, s21_test_0);
  tcase_add_test(tc, s21_test_1);
  tcase_add_test(tc, s21_test_2);
  tcase_add_test(tc, s21_test_3);
  tcase_add_test(tc, calc_test);
  suite_add_tcase(s, tc);

  return s;
}

int main(void) {
  int number_failed;
  SRunner *sr = srunner_create(NULL);
  srunner_add_suite(sr, calc_str_suite());
  srunner_set_log(sr, "test.log");
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
