#include "butterfly.h"
#include <math.h>
#include <QTimerEvent>
#include <QRandomGenerator>

const static double PI=3.1416;

Butterfly::Butterfly()
{
    setFlag(QGraphicsItem::ItemIsMovable);

    pix_up.load("up.png");
    pix_down.load("down.png");
    up = true;
    startTimer(100);
}

QRectF Butterfly::boundingRect() const // define the region of butterfly's flying
{
    qreal adjust = 8;
    return QRectF(-pix_up.width()/2-adjust,-pix_up.height()/2-adjust,
                pix_up.width()+adjust*2,pix_up.height()+2*adjust);
}

void Butterfly::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(up) // if drawing up this time, draw down the next time.
    {
        painter->drawPixmap(boundingRect().topLeft(),pix_up);
        up = !up;
    }
    else
    {
        painter->drawPixmap(boundingRect().topLeft(),pix_down);
        up = !up;
    }
}

void Butterfly::timerEvent(QTimerEvent *)
{
    // scene edge control
    qreal edgex = scene()->sceneRect().right()+boundingRect().width()/2; // scene(): current item's scene
    qreal edgetop = scene()->sceneRect().top()+boundingRect().height()/2;
    qreal edgebottom = scene()->sceneRect().bottom()+boundingRect().height()/2;
    //qDebug() << scene()->itemsBoundingRect();
    if (pos().x() >= edgex)
        setPos(scene()->sceneRect().left(),pos().y());              // if out of region, then start from start point
    if (pos().y() <= edgetop)
        setPos(pos().x(),scene()->sceneRect().bottom());
    if (pos().y() >= edgebottom)
        setPos(pos().x(),scene()->sceneRect().top());

//    angle += (qrand()%10)/20.0;
    QRandomGenerator *qrandom = new QRandomGenerator;               //instead obsolated qrand()
    angle += qrandom->generate();
    qreal dx = fabs(sin(angle*PI)*10.0);
    qreal dy = (qrandom->generate()%20)-10.0;
    setPos(mapToParent(dx,dy)); // map (dx, dy) to its parent scene coordinate system. Return to the converted point
    update();
}
