#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  if (watched == ui->paint_widget && event->type() == QEvent::Paint) {
    showPaint();
  }
  return QWidget::eventFilter(watched, event);
}

int MainWindow::getDigitOfUnsignedNum(unsigned int n) {
  int i = 1;
  while (n /= 10) {
    i++;
  }
  return i;
}
int MainWindow::getOneBitOfUnsignedNumFromRight(unsigned int x,
                                                unsigned int y) {
  QString strX = QString::number(x);
  if (strX.mid(y - 1, 1) == "")
    return 0;
  else
    return strX.mid(strX.length() - y, 1).toInt();
}

int MainWindow::biggestNumInQList(QList<int> intList) {
  int max = intList[0];
  for (int i = 0; i < intList.length(); i++) {
    if (max < intList[i]) max = intList[i];
  }
  return max;
}

void MainWindow::showPaint() {
  int biggerInput = ui->spinBox->value() > ui->spinBox_2->value()
                        ? ui->spinBox->value()
                        : ui->spinBox_2->value(),
      smallerInput = ui->spinBox->value() == biggerInput
                         ? ui->spinBox_2->value()
                         : ui->spinBox->value(),
      curX = width() / 2, curY = 40, result = biggerInput + smallerInput,
      carryBit = 0;
  QFont font, errFont, smFont;
  QPainter painter(ui->paint_widget);
  font.setPixelSize(34);
  errFont.setPixelSize(34);
  errFont.setBold(true);
  smFont.setPixelSize(14);
  painter.setPen(Qt::black);
  painter.setFont(font);
  switch (ui->comboBox->currentIndex()) {
    case 0:  // plus
      painter.drawText(curX, curY, QString::number(biggerInput));
      curY += font.pixelSize();
      if (((getDigitOfUnsignedNum(biggerInput) == 2) &&
           (getDigitOfUnsignedNum(smallerInput == 1))) ||
          ((getDigitOfUnsignedNum(biggerInput) == 3) &&
           (getDigitOfUnsignedNum(smallerInput) == 2))) {
        curX += font.pixelSize() / 2;
      }
      if ((getDigitOfUnsignedNum(biggerInput) == 3) &&
          (getDigitOfUnsignedNum(smallerInput) == 1)) {
        curX += font.pixelSize();
      }
      if ((getDigitOfUnsignedNum(biggerInput) ==
           getDigitOfUnsignedNum(smallerInput)) &&
          (getDigitOfUnsignedNum(smallerInput) == 2)) {
        curX -= font.pixelSize() / 2;
      }
      painter.drawText(curX, curY, QString::number(smallerInput));

      //      show result
      curX += font.pixelSize() / 2 * (getDigitOfUnsignedNum(smallerInput) - 1);
      curY += 10 + font.pixelSize();
      for (int i = 1; i <= getDigitOfUnsignedNum(result); i++) {
        carryBit = (getOneBitOfUnsignedNumFromRight(biggerInput, i) +
                    getOneBitOfUnsignedNumFromRight(smallerInput, i)) > 9
                       ? 1
                       : 0;
        painter.drawText(
            curX, curY - 10,
            QString::number(getOneBitOfUnsignedNumFromRight(result, i)));
        if (bool(carryBit)) {
          painter.setFont(smFont);
          painter.drawText(curX - 3, curY - font.pixelSize() - 6, "1");
          painter.setFont(font);
        }
        curX -= font.pixelSize() / 2;
      }
      //      draw plus sign
      curY -= font.pixelSize() + 7;
      painter.drawText(curX, curY, "+");
      //      draw result line
      curY += 2;
      painter.drawLine(
          curX - 5, curY,
          curX + font.pixelSize() / 2 * (getDigitOfUnsignedNum(result) + 1) + 5,
          curY);
      break;
    case 1:  // subtract
      painter.drawText(width() / 2, height() / 2,
                       QString::number(ui->spinBox->value()) + "-" +
                           QString::number(ui->spinBox_2->value()));
      break;
    case 2:  // multiply
      painter.drawText(width() / 2, height() / 2,
                       QString::number(ui->spinBox->value()) + "*" +
                           QString::number(ui->spinBox_2->value()));
      break;
    case 3:  // devide
      if (ui->spinBox_2->value() == 0) {
        painter.setPen(QColor(255, 0, 0));
        painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter,
                         "除数为0的除法算式没有意义！");
        return;
      }
      painter.drawText(width() / 2, height() / 2,
                       QString::number(ui->spinBox->value()) + "/" +
                           QString::number(ui->spinBox_2->value()));
      break;
  }
}

void MainWindow::on_pushButton_clicked() {
  ui->paint_widget->installEventFilter(this);
  update();
}
