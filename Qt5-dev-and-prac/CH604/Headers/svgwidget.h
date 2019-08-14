#ifndef SVGWIDGET_H
#define SVGWIDGET_H

#include <QtSvg>
#include <QSvgWidget>
#include <QSvgRenderer> // Qt makefile .pro should add "QT += svg"

class SvgWidget : public QSvgWidget
{
    Q_OBJECT
public:
    SvgWidget(QWidget *parent=0);           // This widget is to hold svg image
    void wheelEvent(QWheelEvent *);         // widget should response the mainwindow wheelevent

private:
    QSvgRenderer *render;
};

#endif // SVGWIDGET_H
