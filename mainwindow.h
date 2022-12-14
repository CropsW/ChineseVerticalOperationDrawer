#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QLine>
#include <QVector>

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  bool eventFilter(QObject *watched, QEvent *event);
  void showPaint();
  static int getDigitOfUnsignedNum(unsigned n);
  static int getOneBitOfUnsignedNumFromRight(unsigned int x, unsigned int y);
  static int biggestNumInQList(QList<int> intList);
  static int getHowManyEndZerosOfUnsignedNum(unsigned int num);
  static int clearAllendZerosOfUnsignedNum(unsigned int num);
};
#endif // MAINWINDOW_H
