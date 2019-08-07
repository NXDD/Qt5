#include "paintarea.h"
#include <QPainter>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent) //初始化主界面
{
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400, 400);
}

void PaintArea::setShape(Shape s) //传入shape后对当前页面进行重绘
{
    shape = s;
    update();
}

void PaintArea::setPen(QPen p) //传入pen后对当前页面进行重绘
{
    pen = p;
    update();
}

void PaintArea::setBrush(QBrush b) //传入brush后对当前页面进行重绘
{
    brush = b;
    update();
}

void PaintArea::setFillRule(Qt::FillRule rule) //传入填充规则后对当前页面进行重绘
{
    fillRule = rule;
    update();
}


void PaintArea::paintEvent(QPaintEvent *) // 执行update()后自动调用paintEvent，对当前图线进行重绘
{
    QPainter p(this); //获取当前画笔
    p.setPen(pen);
    p.setBrush(brush); //获取当前画刷
    QRect rect(50, 100, 300, 200); //所显示的矩形形状
    static const QPoint points[4] =
    {
        QPoint(150, 100), QPoint(300, 150), QPoint(350, 250), QPoint(100, 300)
    }; // 画多边形的四个点

    int startAngle = 30*16; //弧的起始角和跨度。30°起，正向跨120°。
    int spanAngle = 120*16;

    QPainterPath path; //画路径（一个矩形+两条弧线）
    path.addRect(150, 150, 100, 100);
    path.moveTo(100, 100);
    path.cubicTo(300, 100, 200, 200, 300, 300);
    path.cubicTo(100, 300, 200, 200, 100, 100);
    path.setFillRule(fillRule);

    switch(shape) //对当前不同的shape调用不同的case，画笔画图。drawLine等函数都是Qt默认函数
    {
    case Line:
        p.drawLine(rect.topLeft(), rect.bottomRight());
        break;
    case Rectangle:
        p.drawRect(rect);
        break;
    case RoundRect:
        p.drawRoundRect(rect);
        break;
    case Ellipse:
        p.drawEllipse(rect);
        break;
    case Polygon:
        p.drawPolygon(points, 4);
        break;
    case Polyline:
        p.drawPolyline(points, 4);
        break;
    case Points:
        p.drawPoints(points, 4);
        break;
    case Arc:
        p.drawArc(rect, startAngle, spanAngle);
        break;
    case Path:
        p.drawPath(path);
        break;
    case Text:
        p.drawText(rect, Qt::AlignCenter, tr("Hello Qt!"));
        break;
    case Pixmap:
        p.drawPixmap(150, 150, QPixmap("butterfly.jpg"));
        break;
    default:
        break;
    }

}
