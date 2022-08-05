#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->comboBox->setCurrentIndex(2); // debug
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
  if (watched == ui->paint_widget && event->type() == QEvent::Paint)
  {
    showPaint();
  }
  return QWidget::eventFilter(watched, event);
}

int MainWindow::getDigitOfUnsignedNum(unsigned int n)
{
  int i = 1;
  while (n /= 10)
  {
    i++;
  }
  return i;
}
int MainWindow::getOneBitOfUnsignedNumFromRight(unsigned int x,
                                                unsigned int y)
{
  QString strX = QString::number(x);
  if (strX.mid(y - 1, 1) == "")
    return 0;
  else
    return strX.mid(strX.length() - y, 1).toInt();
}

int MainWindow::biggestNumInQList(QList<int> intList)
{
  int max = intList[0];
  for (int i = 0; i < intList.length(); i++)
  {
    if (max < intList[i])
      max = intList[i];
  }
  return max;
}

int MainWindow::getHowManyEndZerosOfUnsignedNum(unsigned int num)
{
  int count = (num == 0);
  for (int i = 10; i <= num; i *= 10)
  {
    if (num % i == 0)
      count++;
  }
  return count;
}

int MainWindow::clearAllendZerosOfUnsignedNum(unsigned int num)
{
  while (num % 10 == 0)
  {
    num /= 10;
  }
  return num;
}

void MainWindow::showPaint()
{

  QFont font, smFont, mutliSignFont;
  QPainter painter(ui->paint_widget);
  font.setPixelSize(34);
  smFont.setPixelSize(14);
  mutliSignFont.setPixelSize(20);
  painter.setPen(Qt::black);
  painter.setFont(font);
  if (ui->spinBox->value() < ui->spinBox_2->value() && ui->comboBox->currentIndex() == 1)
  {
    painter.setPen(QColor(255, 128, 0));
    painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter,
                     "暂不支持负数运算！");
    return;
  }
  int biggerInput = ui->spinBox->value() > ui->spinBox_2->value()
                        ? ui->spinBox->value()
                        : ui->spinBox_2->value(),
      smallerInput = ui->spinBox->value() == biggerInput
                         ? ui->spinBox_2->value()
                         : ui->spinBox->value(),
      curX = width() / 2, curY = 40, result, bNo0, tmp;
  switch (ui->comboBox->currentIndex())
  {
  case 0: // plus
    result = biggerInput + smallerInput;
    painter.drawText(curX, curY, QString::number(biggerInput));
    curY += font.pixelSize();
    curX += font.pixelSize() / 2 * (getDigitOfUnsignedNum(biggerInput) - getDigitOfUnsignedNum(smallerInput));
    painter.drawText(curX, curY, QString::number(smallerInput));

    //      show result
    curX += font.pixelSize() / 2 * (getDigitOfUnsignedNum(smallerInput) - 1);
    curY += 10 + font.pixelSize();
    for (int i = 1; i <= getDigitOfUnsignedNum(result); i++)
    {
      painter.drawText(
          curX, curY - 10,
          QString::number(getOneBitOfUnsignedNumFromRight(result, i)));
      if ((getOneBitOfUnsignedNumFromRight(biggerInput, i) +
           getOneBitOfUnsignedNumFromRight(smallerInput, i)) > 9)
      {
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
  case 1: // subtract
    result = biggerInput - smallerInput;
    painter.drawText(curX, curY, QString::number(biggerInput));
    curY += font.pixelSize();
    curX += font.pixelSize() / 2 * (getDigitOfUnsignedNum(biggerInput) - getDigitOfUnsignedNum(smallerInput));
    painter.drawText(curX, curY, QString::number(smallerInput));

    //      show result
    curX += font.pixelSize() / 2 * (getDigitOfUnsignedNum(smallerInput) - 1);
    curY += 10 + font.pixelSize();
    for (int i = 1; i <= getDigitOfUnsignedNum(result); i++)
    {
      painter.drawText(
          curX, curY - 10,
          QString::number(getOneBitOfUnsignedNumFromRight(result, i)));
      curX -= font.pixelSize() / 2;
      if (getOneBitOfUnsignedNumFromRight(biggerInput, i) < getOneBitOfUnsignedNumFromRight(smallerInput, i))
      {
        curY -= font.pixelSize() * 3;
        painter.setBrush(Qt::black);
        painter.drawEllipse(curX + font.pixelSize() / 4 - 2, curY - 5, 4, 4);
        painter.setBrush(Qt::NoBrush);
        curY += font.pixelSize() * 3;
      }
    }
    if (getDigitOfUnsignedNum(biggerInput) > getDigitOfUnsignedNum(result))
      curX -= font.pixelSize() / 2 * (getDigitOfUnsignedNum(biggerInput) - getDigitOfUnsignedNum(result));
    //      draw subtract sign
    curY -= font.pixelSize() + 7;
    painter.drawText(curX, curY, "-");
    //      draw result line
    curY += 2;
    painter.drawLine(
        curX - 5, curY,
        curX + font.pixelSize() / 2 * (getDigitOfUnsignedNum(biggerInput) + 1) + 5,
        curY);
    break;
  case 2: // multiply
    result = biggerInput * smallerInput;

    // put the end zero(s) of smallerInput to biggerInput
    while (biggerInput % 10 == 0)
    {
      biggerInput /= 10;
      smallerInput *= 10;
    }
    while (smallerInput % 10 == 0)
    {
      smallerInput /= 10;
      biggerInput *= 10;
    }

    bNo0 = clearAllendZerosOfUnsignedNum(biggerInput);
    painter.drawText(curX, curY, QString::number(bNo0 > smallerInput ? biggerInput : smallerInput));
    curY += font.pixelSize();
    curX += font.pixelSize() / 2 * (getDigitOfUnsignedNum(bNo0 > smallerInput ? biggerInput : smallerInput) - getDigitOfUnsignedNum(clearAllendZerosOfUnsignedNum(bNo0 > smallerInput ? smallerInput : biggerInput)) - getHowManyEndZerosOfUnsignedNum(bNo0 > smallerInput ? biggerInput : smallerInput));
    painter.drawText(curX, curY, QString::number(bNo0 > smallerInput ? smallerInput : biggerInput));

    if (smallerInput > 9)
    { // at least 2 digits

      int results[getDigitOfUnsignedNum(bNo0 > smallerInput ? smallerInput : biggerInput)];
      // calc results
      for (int i = 0; i < getDigitOfUnsignedNum(bNo0 > smallerInput ? smallerInput : biggerInput); i++)
        results[i] = clearAllendZerosOfUnsignedNum(bNo0 > smallerInput ? biggerInput : smallerInput) * getOneBitOfUnsignedNumFromRight(bNo0 > smallerInput ? smallerInput : biggerInput, i + 1);
      curX += font.pixelSize() / 2 * (getDigitOfUnsignedNum(bNo0 > smallerInput ? smallerInput : biggerInput) - 1);
      for (int i = 0; i < getDigitOfUnsignedNum(bNo0 > smallerInput ? smallerInput : biggerInput); i++)
      {
        curY += font.pixelSize();

        tmp = curX;
        for (int j = 1; j <= getDigitOfUnsignedNum(results[i]); j++)
        {
          if (results[i] == 0)
          {
            curY -= font.pixelSize();
            break;
          }
          painter.drawText(tmp, curY, QString::number(getOneBitOfUnsignedNumFromRight(results[i], j)));
          tmp -= font.pixelSize() / 2;
        }
        curX -= font.pixelSize() / 2;
      }

      // draw plus sign
      curX -= font.pixelSize() / 2 * (getDigitOfUnsignedNum(results[getDigitOfUnsignedNum(bNo0 > smallerInput ? smallerInput : biggerInput) - 1]) - 1);
      curY = 40 + font.pixelSize();
      // painter.drawPoint(curX, curY);
      painter.setFont(mutliSignFont);
      painter.drawText(curX, curY, "×");

      // draw the 1st line and result line
      painter.drawLines(
          QVector<QLine>()
          << QLine(curX - 5, curY + 2,
                   width() / 2 +
                       font.pixelSize() / 2 *
                           (getDigitOfUnsignedNum(bNo0 > smallerInput
                                                      ? biggerInput
                                                      : smallerInput) +
                            getHowManyEndZerosOfUnsignedNum(
                                bNo0 > smallerInput ? smallerInput
                                                    : biggerInput)) +
                       5,
                   curY + 2)
          << QLine(curX - 5,
                   curY + 2 +
                       font.pixelSize() *
                           getDigitOfUnsignedNum(clearAllendZerosOfUnsignedNum(bNo0 > smallerInput
                                                                                   ? smallerInput
                                                                                   : biggerInput)),
                   width() / 2 +
                       font.pixelSize() / 2 *
                           (getDigitOfUnsignedNum(bNo0 > smallerInput
                                                      ? biggerInput
                                                      : smallerInput) +
                            getHowManyEndZerosOfUnsignedNum(
                                bNo0 > smallerInput ? smallerInput
                                                    : biggerInput)) +
                       5,
                   curY + 2 +
                       font.pixelSize() *
                           getDigitOfUnsignedNum(clearAllendZerosOfUnsignedNum(bNo0 > smallerInput
                                                                                   ? smallerInput
                                                                                   : biggerInput))));

      // show finally result
      curY += font.pixelSize() * (getDigitOfUnsignedNum(clearAllendZerosOfUnsignedNum(bNo0 > smallerInput ? smallerInput : biggerInput)) + 1);
      curX = width() / 2 + font.pixelSize() / 2 * (getDigitOfUnsignedNum(bNo0 > smallerInput ? biggerInput : smallerInput) + getHowManyEndZerosOfUnsignedNum(bNo0 > smallerInput ? smallerInput : biggerInput) - 1);
      painter.drawPoint(curX, curY);
      painter.setFont(font);
      for (int i = 1; i <= getDigitOfUnsignedNum(result); i++)
      {
        painter.drawText(curX, curY, QString::number(getOneBitOfUnsignedNumFromRight(result, i)));
        curX -= font.pixelSize() / 2;
      }
    }
    else
    { // only 1 digit
      // show result
      curX += font.pixelSize() / 2 * (getDigitOfUnsignedNum(smallerInput) - 1);
      curY += 10 + font.pixelSize();
      curX += font.pixelSize() / 2 * getHowManyEndZerosOfUnsignedNum(biggerInput);
      for (int i = 1; i <= getDigitOfUnsignedNum(result); i++)
      {
        painter.drawText(
            curX, curY - 10,
            QString::number(getOneBitOfUnsignedNumFromRight(result, i)));

        curX -= font.pixelSize() / 2;
        if (getOneBitOfUnsignedNumFromRight(biggerInput, i) * smallerInput > 9)
        {
          painter.setFont(smFont);
          painter.drawText(curX - 3 + font.pixelSize() / 2, curY - font.pixelSize() - 6, QString::number(getOneBitOfUnsignedNumFromRight(getOneBitOfUnsignedNumFromRight(biggerInput, i) * smallerInput, 2)));
          painter.setFont(font);
        }
      }
      //      draw multi sign
      curY -= font.pixelSize() + 7;
      painter.setFont(mutliSignFont);
      painter.drawText(curX, curY, "×");
      //      draw result line
      if (getDigitOfUnsignedNum(biggerInput) > getDigitOfUnsignedNum(result))
        curX -= font.pixelSize() / 2 * (getDigitOfUnsignedNum(biggerInput) - getDigitOfUnsignedNum(result));
      curY += 2;
      painter.drawLine(
          curX - 5, curY,
          curX + font.pixelSize() / 2 * (getDigitOfUnsignedNum(result) + 1) + 5,
          curY);
    }
    break;
  case 3: // devide
    if (ui->spinBox_2->value() == 0)
    {
      painter.setPen(Qt::red);
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

void MainWindow::on_pushButton_clicked()
{
  ui->paint_widget->installEventFilter(this);
  update();
}
