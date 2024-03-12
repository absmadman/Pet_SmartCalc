#ifndef CREDIT_H
#define CREDIT_H

#include <QMainWindow>

extern "C" {
#include "back/credit_back.h"
}

namespace Ui {
class credit;
}

class credit : public QMainWindow {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_push_calc_clicked();

 private:
  double DiffMonthly(double loan, double rate, double period);
  void AppendLabelStr(std::string *label_str, double monthly, int i);
  Ui::credit *ui;
};

#endif  // CREDIT_H
