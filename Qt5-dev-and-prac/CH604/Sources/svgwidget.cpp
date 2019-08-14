#include "svgwidget.h"

SvgWidget::SvgWidget(QWidget *parent)
    :QSvgWidget(parent)
{
    render = renderer();
}

void SvgWidget::wheelEvent(QWheelEvent *event)
{
    const double diff = 0.1;
    QSize size = render->defaultSize();
    int width = size.width();
    int height = size.height();
    if (event->delta()>0) // use delta() to get the mousewheel distance.
    {
        width = int(this->width()+this->width()*diff); // enlarge the svg render size
        height = int(this->height()+this->height()*diff);
    }
    else
    {
        width = int(this->width() - this->width()*diff);  // shrink the svg render size
        height = int(this->height() - this->height()*diff);
    }
    resize(width, height);
}
