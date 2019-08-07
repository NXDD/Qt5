#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));             //设置填充
    pix = new QPixmap(size());
    pix->fill(Qt::white);
    setMinimumSize(600, 400);
}

void DrawWidget::setStyle(int s)
{
    style = s;
}

void DrawWidget::setWidth(int w)
{
    weight = w;
}

void DrawWidget::setColor(QColor c)
{
    color = c;
}

void DrawWidget::mousePressEvent(QMouseEvent *e) //按下鼠标时，记录下此时鼠标所在位置
{
    startPos = e->pos();
}

void DrawWidget::mouseMoveEvent(QMouseEvent *e) //在鼠标移动的过程中画图。新建painter绘图，图线画到pix中，作为缓存。鼠标->pix，pix->this
{
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle((Qt::PenStyle)style);          //强制类型转换，int->Qt::PenStyle
    pen.setColor(color);
    pen.setWidth(weight);
    painter->begin(pix);                        //begin：开始画图；end：停止画图。若绘制内部对象则不必用begin和end。
                                                //QPainter p; p.begin(this);...p.end(); == QPainter p(this);
    painter->setPen(pen);
    painter->drawLine(startPos, e->pos());      //绘制鼠标从startPos到当前位置的曲线
    painter->end();
    startPos = e->pos();                        //更新鼠标位置，为下次绘图做准备。下次绘图的startPos即为现在鼠标所在位置
    update();                                   //更新重绘，执行paintEvent
}

void DrawWidget::paintEvent(QPaintEvent *)      //把pix画到主窗口中
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);     //以（0， 0）为原点，画pix
}

void DrawWidget::resizeEvent(QResizeEvent *e)
{
    if(height()>pix->height()||width()>pix->width()) //如果当前窗口尺寸大于原pix尺寸，则扩大画布面积。否则无动作。
    {
        QPixmap *newPix = new QPixmap(size());       //1. 以当前的size建立新的pix
        newPix->fill(Qt::white);                     //2. 新的pix填充为白色
        QPainter p(newPix);                          //3. 以新的pix为parent，创建新的painter
        p.drawPixmap(QPoint(0, 0), *pix);            //4. 以（0， 0）为原点，画原来pix的内容
        pix = newPix;                                //5. 将newPix赋值给pix，作为新的QPixmap对象
    }
    QWidget::resizeEvent(e);
}

void DrawWidget::clear()                             //用一个全新的干净的QPixmap来代替pix，并重绘
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    pix = clearPix;
    update();
}
