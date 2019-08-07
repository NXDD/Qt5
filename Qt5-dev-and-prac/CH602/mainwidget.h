#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGradient>

#include "paintarea.h"

// 绘图区域对象的声明
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    PaintArea *paintArea; //绘图区

    QLabel *shapeLabel; //图线形状
    QComboBox *shapeComboBox;

    QLabel *penWidthLabel; //画笔线宽
    QSpinBox *penWidthSpinBox;

    QLabel *penColorLabel; //画笔颜色
    QFrame *penColorFrame;
    QPushButton *penColorBtn;

    QLabel *penStyleLabel; //画笔图线类型
    QComboBox *penStyleComboBox;

    QLabel *penCapLabel; //画笔笔帽
    QComboBox *penCapComboBox;

    QLabel *penJoinLabel; //画笔连接点类型
    QComboBox *penJoinComboBox;

    QLabel *fillRuleLabel; //填充模式
    QComboBox *fillRuleComboBox;

    QLabel *spreadLabel; //铺展效果
    QComboBox *spreadComboBox;
    QGradient::Spread spread;

    QLabel *brushStyleLabel; //画刷风格
    QComboBox *brushStyleComboBox;

    QLabel *brushColorLabel; //画刷颜色
    QFrame *brushColorFrame;
    QPushButton *brushColorBtn;

    QGridLayout *rightLayout; //总布局

protected slots:
    void ShowShape(int); //显示形状
    void ShowPenWidth(int); //显示笔的粗细
    void ShowPenColor(); //显示笔的颜色
    void ShowPenStyle(int); //显示画笔图线类型
    void ShowPenCap(int); //显示笔帽
    void ShowPenJoin(int); //显示画笔连接点
    void ShowSpreadStyle(); //显示铺展效果
    void ShowFillRule(); //显示填充
    void ShowBrushColor(); //显示画刷颜色
    void ShowBrush(int); //显示画刷风格
};

#endif // MAINWIDGET_H
