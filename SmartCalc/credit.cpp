#include "credit.h"

#include <QLabel>
#include <iostream>

#include "ui_credit.h"
credit::credit(QWidget *parent) : QMainWindow(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  ui->spinBox->setMaximum(10000000);
  //    ui->spinBox->maximum(100000);
}

credit::~credit() { delete ui; }

void credit::on_push_calc_clicked() {
  std::string str_monthly;
  double monthly_pay;
  double overpay;
  double total_pay;
  double loan = ui->spinBox->value();
  double period = ui->spinBox_2->value();
  double rate = ui->doubleSpinBox->value();
  if (ui->comboBox->currentText() == "Annuity") {
    monthly_pay = monthy_anu(loan, rate, period);
    overpay = overpayment(loan, rate, period);
    total_pay = total(loan, rate, period);
    str_monthly = std::to_string(monthly_pay);
  } else {
    overpay = overpayment_diff(loan, rate, period);
    total_pay = total_diff(loan, rate, period);
    monthly_pay = DiffMonthly(loan, rate, period);
    str_monthly = std::to_string((int)monthly_pay);
    str_monthly.append(" mean");
  }
  std::string str_overpay = std::to_string(overpay);
  QString overpay_qstr = QString::fromStdString(str_overpay);

  std::string str_total = std::to_string(total_pay);
  QString total_qstr = QString::fromStdString(str_total);
  QString monthly_qstr = QString::fromStdString(str_monthly);

  ui->textEdit_2->setText(overpay_qstr);
  ui->textEdit_3->setText(total_qstr);
  ui->textEdit->setText(monthly_qstr);
}

double credit::DiffMonthly(double loan, double rate, double period) {
  std::string label_str;
  double all_monthly = 0;
  double monthly_now = 0;
  double minus = loan / period;
  for (int i = period; i > 0; i -= 1) {
    monthly_now = monthy_diff(loan, rate, i);
    all_monthly += monthly_now;
    AppendLabelStr(&label_str, monthly_now, i);
    loan -= minus;
  }
  QLabel *label = new QLabel(QString::fromStdString(label_str));
  label->show();
  return all_monthly / period;
}

void credit::AppendLabelStr(std::string *label_str, double monthly, int i) {
  std::string monthly_str = std::to_string(monthly);
  std::string i_str = std::to_string(i);
  label_str->append("Платеж №:");
  label_str->append(i_str);
  label_str->append("   ");
  label_str->append("Сумма:");
  label_str->append("   ");
  label_str->append(monthly_str);
  label_str->append("\n");
}
