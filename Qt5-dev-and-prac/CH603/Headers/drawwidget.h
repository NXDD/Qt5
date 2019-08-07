#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>

#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>
#include <QPen>


class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

signals:


public slots:
    void setStyle(int);
    void setWidth(int);
    void setColor(QColor);
    void clear();

private:
    QPixmap *pix;
    QPoint startPos;   //开始绘图
    QPoint endPos;     //停止绘图
    int style;
    int weight;
    QColor color;
};

#endif // DRAWWIDGET_H
