#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstring>
#include <regex>
#include <string>

#include "credit.h"

extern "C" {
#include "back/polishnotation.h"
#include "back/stack.h"
#include "back/stack_for_calculations.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void click_on_digit();
  void if_equal();
  void click_on_helpers();
  void ClickOnOperator();
  void ClickOnTrgn();
  void on_push_graph_clicked();
  void on_spinBox_valueChanged(int arg1);
  void on_spinBox_2_valueChanged(int arg1);
  void on_spinBox_3_valueChanged(int arg1);
  void on_spinBox_4_valueChanged(int arg1);
  void on_push_credit_clicked();
  void on_push_ac_clicked();
  void on_push_dot_clicked();
  void on_push_x_clicked();

  void on_push_mod_clicked();

 private:
  void MoveCursor();
  Ui::MainWindow *ui;
  credit *crdt;
  int ValidOperator();
  void SetSpinboxes();
  void SpacerSqueeze();
  void SpacerExpand();
  void HideSpinboxes();
  void ShowSpinboxes();
  void SetDefaultSpinBoxes();
  int FindLastOperator();
  int FindLastNumber();
  int EndWithDigit();
  double CalcAndGraph(std::string std_str);
  std::string ReplaceTrigonometry(std::string str);
  void SetText(QString result_str);
  QString GetText();
  bool ValidDot();
  bool ValidText();
  void SetTextEdit(QString str);
};
#endif  // MAINWINDOW_H
