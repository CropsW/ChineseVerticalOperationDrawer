# ChineseVerticalOperationDrawer 中国竖式生成器

一个支持为 1000 内简单四则运算生成竖式的软件。

## Framework 架构

Qt Widgets + QPainter

## Idea 想法

1. 每次点击按钮：调用 `eventFilter` 将 QPainter 的范围限定在 `paint_widget`。
2. 所有的绘图都在 `showPaint` 函数。
3. 先获取 `spin_box` 和 `spin_box_2` 的值，在根据大小分别赋值给 `biggerInput` 和 `smallerInput`。
4. 使用整型变量 `curX` 和 `curY` 来存储画笔 `painter` 当前的位置（以后可能会考虑换成 `QPoint` 类型的变量来存储 `painter` 当前的位置）。
5. 初始化 `QFont` 类型的字体配置：
   - `font`：最普通的字体。
   - `smFont`：用来表示进位、退位的字体。
6. 通过 `switch(ui->comboBox->currentIndex())` 分支来区别加减乘除。

### Plus 加法

没有写东西……
因为我懒~

### Subtract 减法

没有写东西……
因为我懒~

### Multiply 乘法

TODO

### Divide 除法

TODO

## Did And Todo 功能

- [x] 基本加法
- [x] 加法（小进位 1）
- [x] 简单减法
- [ ] 减法（结果可为负数）
- [ ] 乘法
- [ ] 除法
  - [x] 报错：`除数为0的除法算式没有意义！`
- [ ] 转为图片
- [ ] 转为图片（可设置背景颜色）

## License 协议

[GNU Global Public License (GPL) v3.0](LICENSE)
