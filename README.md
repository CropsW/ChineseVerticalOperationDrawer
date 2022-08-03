# ChineseVerticalOperationDrawer 中国竖式生成器

一个支持为 1000 内简单四则运算生成竖式的软件。

## Framework 架构

Qt Widgets + QPainter

## Idea 想法

每次点击按钮：调用 `eventFilter` 将 QPainter 的范围限定在 `paint_widget`。
所有的绘图都在 `showPaint` 函数。

### Plus 加法

1. 先获取 `spin_box` 和 `spin_box_2` 的值，在根据大小分别赋值给 `biggerInput` 和 `smallerInput`。
2. 使用整型变量 `curX` 和 `curY` 来存储画笔 `painter` 当前的位置（以后可能会考虑换成 `QPoint` 类型的变量来存储 `painter` 当前的位置）。
3. 初始化 `QFont` 类型的字体配置：
   - `font`：最普通的字体。
   - `errFont`：表示错误的字体，如`除数为0的除法算式没有意义！`使用的就是这种字体。
   - `smFont`：用来表示进位、退位的字体。

### Subtract 减法

### Multiply 乘法

### Divide 除法

## Did And Todo 功能

- [x] 基本加法
- [x] 加法（小进位 1）
- [ ] 减法
- [ ] 乘法
- [ ] 除法
  - [x] 报错：`除数为0的除法算式没有意义！`
- [ ] 转为图片
- [ ] 转为图片（可设置背景颜色）

## License 协议

[GNU Global Public License (GPL) v3.0](LICENSE)
