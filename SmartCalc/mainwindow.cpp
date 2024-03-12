#include "mainwindow.h"

#include <QMessageBox>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setFixedSize(702, 800);
  ui->setupUi(this);
  ui->textEdit->setReadOnly(true);
  ui->text_x->setReadOnly(true);
  SpacerSqueeze();
  SetSpinboxes();
  SetDefaultSpinBoxes();
  HideSpinboxes();
  ui->push_x->hide();
  ui->widget->setFixedSize(550, 500);
  ui->widget->hide();
  crdt = new credit(this);
  crdt->hide();
  connect(ui->push_number_0, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_1, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_2, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_3, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_4, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_5, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_6, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_7, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_8, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_number_9, SIGNAL(clicked()), this, SLOT(click_on_digit()));
  connect(ui->push_open_br, SIGNAL(clicked()), this, SLOT(click_on_helpers()));
  connect(ui->push_close_br, SIGNAL(clicked()), this, SLOT(click_on_helpers()));
  connect(ui->push_minus, SIGNAL(clicked()), this, SLOT(ClickOnOperator()));
  connect(ui->push_plus, SIGNAL(clicked()), this, SLOT(ClickOnOperator()));
  connect(ui->push_divide, SIGNAL(clicked()), this, SLOT(ClickOnOperator()));
  connect(ui->push_mul, SIGNAL(clicked()), this, SLOT(ClickOnOperator()));
  connect(ui->push_degree, SIGNAL(clicked()), this, SLOT(ClickOnOperator()));
  connect(ui->push_sin, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_asin, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_cos, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_acos, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_tan, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_atan, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_log, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_ln, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_sqrt, SIGNAL(clicked()), this, SLOT(ClickOnTrgn()));
  connect(ui->push_equal, SIGNAL(clicked()), this, SLOT(if_equal()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::click_on_digit() {
  QPushButton *button = (QPushButton *)sender();
  QString str = GetText();
  // || str.endsWith('.')  ||

  if (str.length() == 0) {
    str += button->text();
    SetText(str);
  } else if (!ValidOperator() || str.at(str.length() - 1).isDigit() ||
             str.endsWith(".")) {
    str += button->text();
    SetText(str);
    //        ui->textEdit->setText(str);
    //
  }
}

bool MainWindow::ValidText() {
  bool ret = true;
  QString for_check = ui->textEdit->toPlainText();
  if (for_check.length() == 0) {
    ret = false;
  } else if (!for_check.at(for_check.length() - 1).isDigit() &&
             for_check.at(for_check.length() - 1) != ')' &&
             for_check.at(for_check.length() - 1) != 'x') {
    SetText("Error");
    ret = false;
  }
  if (for_check.contains("inf") || for_check.contains("Error") ||
      for_check.contains("too long: max length 256") ||
      for_check.contains("nan")) {
    SetText("");
    ret = false;
  }
  if (for_check.length() > 258) {
    ui->textEdit->setText("too long: max length 256");  // change this later
    ret = false;
  }

  if (for_check.count('(') != for_check.count(')')) {
    SetText("Error");
    ret = false;
  }
  return ret;
}

void MainWindow::SetTextEdit(QString str) {
  ui->textEdit->setText("");
  ui->textEdit->setText(str);
}

void MainWindow::if_equal() {
  ui->widget->clearGraphs();

  QString result_str;
  QString for_check = ui->textEdit->toPlainText();
  QString str = "(" + ui->textEdit->toPlainText() + ")";
  QString str_x = ui->text_x->toPlainText();
  if (!ValidText()) {
    return;
  }
  std::string replaced = str.toStdString();
  if (replaced.find("x") != std::string::npos) {
    std::string std_str_x = str_x.toStdString();
    if (!std_str_x.empty()) {
      replaced = std::regex_replace(replaced, std::regex("x"), std_str_x);
      replaced = ReplaceTrigonometry(replaced);
      CalcAndGraph(replaced);
      double result = calc_str(replaced.c_str());
      result_str = QString::number(result);
      SetTextEdit(result_str);
    } else {
      replaced = ReplaceTrigonometry(replaced);
      CalcAndGraph(replaced);
    }
  } else if (str.length() != 0) {
    replaced = ReplaceTrigonometry(replaced);
    double result = CalcAndGraph(str.toStdString());
    result_str = QString::number(result);
  }
  SetTextEdit(result_str);
  //    ui->textEdit->setText("");
  //    ui->textEdit->setText(result_str);
}

double MainWindow::CalcAndGraph(std::string std_str) {
  QVector<double> x, y;
  double result = 0;
  QString str_x = ui->text_x->toPlainText();
  std::string replace_x = str_x.toStdString();
  double x_min = ui->spinBox_2->value();
  double x_max = ui->spinBox->value();
  while (x_min < x_max) {
    replace_x = std::to_string(x_min);
    if (x_min < 0) {
      replace_x.insert(replace_x.begin(), '(');
      replace_x.insert(replace_x.end(), ')');
    }
    std::string y_val = std::regex_replace(std_str, std::regex("x"), replace_x);
    y_val = ReplaceTrigonometry(y_val);
    result = calc_str(y_val.c_str());
    x.push_back(x_min);
    y.push_back(result);
    x_min += x_max > x_min ? x_max / 1000 : x_min / 1000;
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();

  return result;
}

void MainWindow::MoveCursor() {
  QTextCursor curs = ui->textEdit->textCursor();
  curs.movePosition(QTextCursor::End);
  ui->textEdit->setTextCursor(curs);
}

void MainWindow::click_on_helpers() {
  QPushButton *button = (QPushButton *)sender();
  QString str = GetText();
  if (button->text() == '(') {
    if (!ValidOperator()) {
      str += '(';
    }
  } else if (button->text() == ')') {
    if (str.count("(") > str.count(")") && str.endsWith("(") == false) {
      if (ValidOperator()) {
        str += ')';
      }
    }
  }
  SetText(str);
}

void MainWindow::ClickOnTrgn() {
  QPushButton *button = (QPushButton *)sender();
  QString str = GetText();
  if (!ValidOperator()) {
    str += button->text();
    SetText(str);
  }
}

void MainWindow::ClickOnOperator() {
  QPushButton *button = (QPushButton *)sender();
  QString str = GetText();
  if (ValidOperator() == 1) {
    str += button->text();
    SetText(str);
  }
}

bool MainWindow::ValidDot() {
  QString str = GetText();
  auto it = str.length() - 1;
  for (; it > 0 && str.at(it).isDigit(); --it)
    ;
  return str.mid(it).count(".") == 0;
}

void MainWindow::on_push_graph_clicked() {
  static int times = 0;
  if (times % 2 == 0) {
    SpacerExpand();
    setFixedSize(1320, 800);
    ui->widget->show();
    ui->push_x->show();
    ShowSpinboxes();
    centralWidget()->setStyleSheet(
        "border-image: url(\":/pictures/bg_wide.png\")  0 0 0 0 stretch "
        "stretch");
  } else {
    SpacerSqueeze();
    ui->widget->hide();
    ui->push_x->hide();
    HideSpinboxes();
    centralWidget()->setStyleSheet(
        "border-image: url(\":/pictures/bg.png\")  0 0 0 0 stretch stretch");
    setFixedSize(702, 800);
  }
  times += 1;
}

void MainWindow::SetSpinboxes() {
  ui->spinBox->setMaximum(1000000);
  ui->spinBox->setMinimum(-1000000);
  ui->spinBox_2->setMaximum(1000000);
  ui->spinBox_2->setMinimum(-1000000);
  ui->spinBox_3->setMaximum(1000000);
  ui->spinBox_3->setMinimum(-1000000);
  ui->spinBox_4->setMaximum(1000000);
  ui->spinBox_4->setMinimum(-1000000);
}

void MainWindow::SpacerSqueeze() {
  ui->horizontalSpacer_5->changeSize(0, 0);
  ui->horizontalSpacer_4->changeSize(0, 0);
  ui->horizontalSpacer_3->changeSize(0, 0);
  ui->horizontalSpacer_2->changeSize(0, 0);
  ui->horizontalSpacer->changeSize(0, 0);
}

void MainWindow::SpacerExpand() {
  ui->horizontalSpacer_5->changeSize(40, 20);
  ui->horizontalSpacer_4->changeSize(30, 20);
  ui->horizontalSpacer_3->changeSize(30, 10);
  ui->horizontalSpacer_2->changeSize(60, 20);
  ui->horizontalSpacer->changeSize(10, 10);
}

void MainWindow::HideSpinboxes() {
  ui->spinBox->hide();
  ui->spinBox_2->hide();
  ui->spinBox_3->hide();
  ui->spinBox_4->hide();
}

void MainWindow::ShowSpinboxes() {
  ui->spinBox->show();
  ui->spinBox_2->show();
  ui->spinBox_3->show();
  ui->spinBox_4->show();
}

void MainWindow::SetDefaultSpinBoxes() {
  ui->spinBox->setValue(5);
  ui->spinBox_2->setValue(0);
  ui->spinBox_3->setValue(5);
  ui->spinBox_4->setValue(0);
}

void MainWindow::on_spinBox_valueChanged(int arg1) {
  ui->widget->xAxis->setRange(arg1, ui->spinBox_2->value());
  ui->widget->replot();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1) {
  ui->widget->xAxis->setRange(ui->spinBox->value(), arg1);
  ui->widget->replot();
}

void MainWindow::on_spinBox_3_valueChanged(int arg1) {
  ui->widget->yAxis->setRange(arg1, ui->spinBox_4->value());
  ui->widget->replot();
}

void MainWindow::on_spinBox_4_valueChanged(int arg1) {
  ui->widget->yAxis->setRange(ui->spinBox_3->value(), arg1);
  ui->widget->replot();
}

void MainWindow::on_push_credit_clicked() {
  if (crdt->isHidden()) {
    crdt->show();
  } else {
    crdt->hide();
  }
}

int MainWindow::ValidOperator() {
  int ret_num = 1;
  QPushButton *button = (QPushButton *)sender();
  QString str = GetText();
  if (button->text() == "-") {
    if (str == "") {
      ret_num = 0;
    } else if (str.endsWith("/") || str.endsWith("+") || str.endsWith("-") ||
               str.endsWith("*") || str.endsWith("^")) {
      ret_num = 0;
    }
  } else {
    if (str == "") {
      ret_num = 0;
    } else if (str.endsWith("/") || str.endsWith("+") || str.endsWith("-") ||
               str.endsWith("*") || str.endsWith("^") || str.endsWith("(") ||
               str.endsWith("%")) {
      ret_num = 0;
    }
  }

  return ret_num;
}

int MainWindow::EndWithDigit() {
  int ret_num = 0;
  QString str = GetText();
  if (str.endsWith("0") || str.endsWith("1") || str.endsWith("2") ||
      str.endsWith("3") || str.endsWith("4") || str.endsWith("5") ||
      str.endsWith("6") || str.endsWith("7") || str.endsWith("8") ||
      str.endsWith("9")) {
    ret_num = 1;
  }
  return ret_num;
}

void MainWindow::on_push_ac_clicked() {
  QString str = "";
  SetText(str);
  //    ui->textEdit->setText(str);
}

int MainWindow::FindLastOperator() {
  QString str = GetText();
  QString operators = "+/*^-";
  int ret_num = 0;
  for (int i = 0; i < operators.length(); i++) {
    if (str.lastIndexOf(operators[i]) > ret_num) {
      ret_num = str.lastIndexOf(operators[i]);
    }
  }
  return ret_num;
}

int MainWindow::FindLastNumber() {
  QString str = GetText();
  QString operators = "1234567890";
  int ret_num = 0;
  for (int i = 0; i < operators.length(); i++) {
    if (str.lastIndexOf(operators[i]) > ret_num) {
      ret_num = str.lastIndexOf(operators[i]);
    }
  }
  return ret_num;
}

void MainWindow::on_push_dot_clicked() {
  QString str = GetText();
  if (ValidDot() && ValidOperator() && !str.endsWith(")")) {
    SetText(str + ".");
    //
  }
}

void MainWindow::on_push_x_clicked() {
  QString str = ui->textEdit->toPlainText();
  if (ValidOperator() == 0 && ui->tabWidget->currentIndex() == 0) {
    str += 'x';
    ui->textEdit->setText(str);
  }
}

std::string MainWindow::ReplaceTrigonometry(std::string str) {
  str = std::regex_replace(str, std::regex("asin"), "S");
  str = std::regex_replace(str, std::regex("acos"), "C");
  str = std::regex_replace(str, std::regex("atan"), "T");
  str = std::regex_replace(str, std::regex("sin"), "s");
  str = std::regex_replace(str, std::regex("cos"), "c");
  str = std::regex_replace(str, std::regex("tan"), "t");
  str = std::regex_replace(str, std::regex("sqrt"), "q");
  str = std::regex_replace(str, std::regex("log"), "L");
  str = std::regex_replace(str, std::regex("ln"), "l");
  return str;
}

void MainWindow::SetText(QString result_str) {
  if (ui->tabWidget->currentIndex() == 0) {
    ui->textEdit->setText("");
    ui->textEdit->setText(result_str);
  } else {
    ui->text_x->setText("");
    ui->text_x->setText(result_str);
  }
}

QString MainWindow::GetText() {
  QString str;
  if (ui->tabWidget->currentIndex() == 0) {
    str = ui->textEdit->toPlainText();
  } else {
    str = ui->text_x->toPlainText();
  }
  return str;
}

void MainWindow::on_push_mod_clicked() {
  QString str = GetText();
  if (ValidOperator()) {
    str += "%";
  }
  SetText(str);
}
