#include <butterfly.h>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(QRectF(-200, -200, 400, 400));  // scene set region

    Butterfly *butterfly = new Butterfly;
    butterfly->setPos(-100, 0);
    scene->addItem(butterfly);                          // scene add item

    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);                              // view set scene
    view->resize(400, 400);
    view->show();

    return a.exec();
}
