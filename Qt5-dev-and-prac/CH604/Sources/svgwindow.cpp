#include "svgwindow.h"

SvgWindow::SvgWindow(QWidget *parent)
    :QScrollArea(parent)
{
    svgWidget = new SvgWidget;
    setWidget(svgWidget);
}

void SvgWindow::setFile(QString fileName)
{
    svgWidget->load(fileName);
    QSvgRenderer *render = svgWidget->renderer();
    svgWidget->resize(render->defaultSize());
}

void SvgWindow::mousePressEvent(QMouseEvent *event)
{
    mousePressPos = event->pos();
    scrollBarValuesOnMousePress.rx() = horizontalScrollBar()->value();
    scrollBarValuesOnMousePress.ry() = verticalScrollBar()->value(); // scrollbar initial pos (ralated to entire window)
    event->accept(); // get the scrollbar initial pos
}

void SvgWindow::mouseMoveEvent(QMouseEvent *event)
{
    horizontalScrollBar()->setValue(scrollBarValuesOnMousePress.x()-(event->pos().x()-mousePressPos.x()));
    // scroll pos = initial scroll pos - mouse move distance
    verticalScrollBar()->setValue(scrollBarValuesOnMousePress.y() - event->pos().y()+mousePressPos.y());
    horizontalScrollBar()->update();
    verticalScrollBar()->update();
    event->accept();
}
