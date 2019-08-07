#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);
public:
    enum Shape{Line,
               Rectangle,
               RoundRect,
               Ellipse,
               Polygon,
               Polyline,
               Points,
               Arc,
               Path,
               Text,
               Pixmap
              };

    //以下几个set函数都涉及到重绘
    void setShape(Shape); //设置形状
    void setPen(QPen); //设置画笔
    void setBrush(QBrush); //设置画刷
    void setFillRule(Qt::FillRule); //设置填充规则
    void paintEvent(QPaintEvent *); //重写paintEvent

signals:

public slots:

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;
};

#endif // PAINTAREA_H
