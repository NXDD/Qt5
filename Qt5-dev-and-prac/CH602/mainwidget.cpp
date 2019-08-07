#include "mainwidget.h"

#include <QColorDialog>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) //初始化主窗口（添加和布局各种控件）
    : QWidget(parent)
{
    paintArea = new PaintArea; //主绘图区

    shapeLabel = new QLabel(tr("形状： "));//形状的label和combo
    shapeComboBox = new QComboBox;
    shapeComboBox->addItem(tr("Line"), PaintArea::Line);
    shapeComboBox->addItem(tr("Rectangle"), PaintArea::Rectangle);
    shapeComboBox->addItem(tr("RoundedRect"), PaintArea::RoundRect);
    shapeComboBox->addItem(tr("Ellipse"), PaintArea::Ellipse);
    shapeComboBox->addItem(tr("Polygon"), PaintArea::Polygon);
    shapeComboBox->addItem(tr("Polyline"), PaintArea::Polyline);
    shapeComboBox->addItem(tr("Points"), PaintArea::Points);
    shapeComboBox->addItem(tr("Arc"), PaintArea::Arc);
    shapeComboBox->addItem(tr("Path"), PaintArea::Path);
    shapeComboBox->addItem(tr("Text"), PaintArea::Text);
    shapeComboBox->addItem(tr("Pixmap"), PaintArea::Pixmap);
    connect(shapeComboBox, SIGNAL(activated(int)), this, SLOT(ShowShape(int))); //setShape(shape)

    penColorLabel = new QLabel(tr("画笔颜色：")); //画笔颜色：colorlabel和更改按钮。更改按钮绑定ShowPenColor（）
    penColorFrame = new QFrame;
    penColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    penColorFrame->setAutoFillBackground(true);
    penColorFrame->setPalette(QPalette(Qt::blue));
    penColorBtn = new QPushButton(tr("更改"));
    connect(penColorBtn, SIGNAL(clicked()), this, SLOT(ShowPenColor()));

    penWidthLabel = new QLabel(tr("画笔线宽：")); //画笔线宽，SpinBox
    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(0, 20);
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ShowPenWidth(int)));

    penStyleLabel = new QLabel(tr("画笔风格：")); //画笔风格：combobox
    penStyleComboBox = new QComboBox;
    penStyleComboBox->addItem(tr("SolidLine"), static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("DotLine"), static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("DashDotLine"), static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("DashDotDotLine"), static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem(tr("CustomDashLine"), static_cast<int>(Qt::CustomDashLine));
    connect(penStyleComboBox, SIGNAL(activated(int)), this, SLOT(ShowPenStyle(int)));

    penCapLabel = new QLabel(tr("画笔顶帽：")); //画笔顶帽：combobox
    penCapComboBox = new QComboBox;
    penCapComboBox->addItem(tr("SquareCap"), Qt::SquareCap);
    penCapComboBox->addItem(tr("FlatCap"), Qt::FlatCap);
    penCapComboBox->addItem(tr("RoundCap"), Qt::RoundCap);
    connect(penCapComboBox, SIGNAL(activated(int)), this, SLOT(ShowPenCap(int)));

    penJoinLabel = new QLabel(tr("画笔连接点：")); //画笔连接点：combobox
    penJoinComboBox = new QComboBox;
    penJoinComboBox->addItem(tr("BevelJoin"), Qt::BevelJoin);
    penJoinComboBox->addItem(tr("MiterJoin"), Qt::MiterJoin);
    penJoinComboBox->addItem(tr("RoundJoin"), Qt::RoundJoin);
    connect(penJoinComboBox, SIGNAL(activated(int)), this, SLOT(ShowPenJoin(int)));

    fillRuleLabel = new QLabel(tr("填充模式：")); //画刷填充模式：combobox
    fillRuleComboBox = new QComboBox;
    fillRuleComboBox->addItem(tr("Odd Even"), Qt::OddEvenFill);
    fillRuleComboBox->addItem(tr("Winding"), Qt::WindingFill);
    connect(fillRuleComboBox, SIGNAL(activated(int)), this, SLOT(ShowFillRule()));

    spreadLabel = new QLabel(tr("铺展效果：")); //画刷铺展效果：combobox
    spreadComboBox = new QComboBox;
    spreadComboBox->addItem(tr("PadSpread"), QGradient::PadSpread);
    spreadComboBox->addItem(tr("RepeatSpread"), QGradient::RepeatSpread);
    spreadComboBox->addItem(tr("ReflectSpread"), QGradient::ReflectSpread);
    connect(spreadComboBox, SIGNAL(activated(int)), this, SLOT(ShowSpreadStyle()));

    brushColorLabel = new QLabel(tr("画刷颜色：")); //类比画笔颜色
    brushColorFrame = new QFrame;
    brushColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    brushColorFrame->setAutoFillBackground(true);
    brushColorFrame->setPalette(QPalette(Qt::green));
    brushColorBtn = new QPushButton(tr("更改"));
    connect(brushColorBtn, SIGNAL(clicked()), this, SLOT(ShowBrushColor()));

    brushStyleLabel = new QLabel(tr("画刷风格：")); //画刷风格：combobox
    brushStyleComboBox = new QComboBox;
    brushStyleComboBox->addItem(tr("SolidPattern"), static_cast<int>(Qt::SolidPattern)); // static_cast<int>:强制类型转换
    brushStyleComboBox->addItem(tr("Dense1Pattern"), static_cast<int>(Qt::Dense1Pattern));
    brushStyleComboBox->addItem(tr("Dense2Pattern"), static_cast<int>(Qt::Dense2Pattern));
    brushStyleComboBox->addItem(tr("Dense3Pattern"), static_cast<int>(Qt::Dense3Pattern));
    brushStyleComboBox->addItem(tr("Dense4Pattern"), static_cast<int>(Qt::Dense4Pattern));
    brushStyleComboBox->addItem(tr("Dense5Pattern"), static_cast<int>(Qt::Dense5Pattern));
    brushStyleComboBox->addItem(tr("Dense6Pattern"), static_cast<int>(Qt::Dense6Pattern));
    brushStyleComboBox->addItem(tr("Dense7Pattern"), static_cast<int>(Qt::Dense7Pattern));
    brushStyleComboBox->addItem(tr("HorPattern"), static_cast<int>(Qt::HorPattern));
    brushStyleComboBox->addItem(tr("VerPattern"), static_cast<int>(Qt::VerPattern));
    brushStyleComboBox->addItem(tr("CrossPattern"), static_cast<int>(Qt::CrossPattern));
    brushStyleComboBox->addItem(tr("BDiagPattern"), static_cast<int>(Qt::BDiagPattern));
    brushStyleComboBox->addItem(tr("DiagCrossPattern"), static_cast<int>(Qt::DiagCrossPattern));
    brushStyleComboBox->addItem(tr("LinearGradientPattern"), static_cast<int>(Qt::LinearGradientPattern));
    brushStyleComboBox->addItem(tr("ConicalGradientPattern"), static_cast<int>(Qt::ConicalGradientPattern));
    brushStyleComboBox->addItem(tr("RadialGradientPattern"), static_cast<int>(Qt::RadialGradientPattern));
    brushStyleComboBox->addItem(tr("TexturePattern"), static_cast<int>(Qt::TexturePattern));

    qDebug()<<"static_cast<int>"<<static_cast<int>(Qt::SolidPattern);
    connect(brushStyleComboBox, SIGNAL(activated(int)), this, SLOT(ShowBrush(int)));

    rightLayout = new QGridLayout; // 右侧这些label，combobox，button的布局
    rightLayout->addWidget(shapeLabel, 0, 0);
    rightLayout->addWidget(shapeComboBox, 0, 1);
    rightLayout->addWidget(penColorLabel, 1, 0);
    rightLayout->addWidget(penColorFrame, 1, 1);
    rightLayout->addWidget(penColorBtn, 1, 2);
    rightLayout->addWidget(penWidthLabel, 2, 0);
    rightLayout->addWidget(penWidthSpinBox, 2, 1);
    rightLayout->addWidget(penStyleLabel, 3, 0);
    rightLayout->addWidget(penStyleComboBox, 3, 1);
    rightLayout->addWidget(penCapLabel, 4, 0);
    rightLayout->addWidget(penCapComboBox, 4, 1);
    rightLayout->addWidget(penJoinLabel, 5, 0);
    rightLayout->addWidget(penJoinComboBox, 5, 1);
    rightLayout->addWidget(fillRuleLabel, 6, 0);
    rightLayout->addWidget(fillRuleComboBox, 6, 1);
    rightLayout->addWidget(spreadLabel, 7, 0);
    rightLayout->addWidget(spreadComboBox, 7, 1);
    rightLayout->addWidget(brushColorLabel, 8, 0);
    rightLayout->addWidget(brushColorFrame, 8, 1);
    rightLayout->addWidget(brushColorBtn, 8, 2);
    rightLayout->addWidget(brushStyleLabel, 9, 0);
    rightLayout->addWidget(brushStyleComboBox, 9, 1)
            ;
    QHBoxLayout *mainLayout = new QHBoxLayout(this); //水平布局，左边paintArea，右边rightlayout
    mainLayout->addWidget(paintArea);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(paintArea, 1);
    mainLayout->setStretchFactor(rightLayout, 0);

    ShowShape(shapeComboBox->currentIndex()); //初始默认显示第一个shape
}

MainWidget::~MainWidget()
{

}

void MainWidget::ShowShape(int value) //获取当前comboBox选定的形状，并执行setShape去执行update（）重绘。
{
    PaintArea::Shape shape = PaintArea::Shape(shapeComboBox->itemData(value, Qt::UserRole).toInt());
    paintArea->setShape(shape);
}

void MainWidget::ShowPenColor() //在ColorDialog中改变颜色，然后得到当前的画笔颜色，线粗，线类型，笔帽，笔连接类型，再执行setPen重绘shape
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::blue)); //默认值为blue。当在ColorDialog中选定新的颜色并按下OK后，color变为新选定的颜色。
    penColorFrame->setPalette(QPalette(color));
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(), Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(), Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(), Qt::UserRole).toInt());
    paintArea->setPen(QPen(color, value, style, cap, join));
}

void MainWidget::ShowPenWidth(int value) //更改线宽
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(), Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(), Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(), Qt::UserRole).toInt());
    paintArea->setPen(QPen(color, value, style, cap, join));
}

void MainWidget::ShowPenStyle(int styleValue) //更改笔的类型
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(styleValue, Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(), Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(), Qt::UserRole).toInt());
    paintArea->setPen(QPen(color, value, style, cap, join));
}

void MainWidget::ShowPenCap(int capValue) //更改笔帽
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(), Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(capValue, Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(), Qt::UserRole).toInt());
    paintArea->setPen(QPen(color, value, style, cap, join));
}

void MainWidget::ShowPenJoin(int joinValue) //更改笔连接点
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(), Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(), Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(joinValue, Qt::UserRole).toInt());
    paintArea->setPen(QPen(color, value, style, cap, join));
}

void MainWidget::ShowFillRule() //更改填充类型
{
    Qt::FillRule rule = Qt::FillRule(fillRuleComboBox->itemData(fillRuleComboBox->currentIndex(), Qt::UserRole).toInt());
    paintArea->setFillRule(rule);
}

void MainWidget::ShowSpreadStyle() //更改铺展类型
{
    spread = QGradient::Spread(spreadComboBox->itemData(spreadComboBox->currentIndex(), Qt::UserRole).toInt());
}

void MainWidget::ShowBrushColor() //设置画刷颜色，然后调用ShowBrush设置画刷性质
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::blue)); //默认蓝色
    brushColorFrame->setPalette(QPalette(color));
    ShowBrush(brushStyleComboBox->currentIndex());
}

void MainWidget::ShowBrush(int value) //如果是样式填充，则setBrush（样式）；如果是纯色填充，则setBrush（color， style）
{
    QColor color = brushColorFrame->palette().color(QPalette::Window);
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(value, Qt::UserRole).toInt());
    if (style == Qt::LinearGradientPattern)
    {
        QLinearGradient linearGradient(0, 0, 400, 400);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, color);
        linearGradient.setColorAt(1.0, Qt::black);
        linearGradient.setSpread(spread);
        paintArea->setBrush(linearGradient);
    }
    else if (style == Qt::RadialGradientPattern)
    {
        QRadialGradient radialGradient(200, 200, 150, 150, 100);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, color);
        radialGradient.setColorAt(1.0, Qt::black);
        radialGradient.setSpread(spread);
        paintArea->setBrush(radialGradient);
    }
    else if (style == Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradient(200, 200, 30);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, color);
        conicalGradient.setColorAt(1.0, Qt::black);
        paintArea->setBrush(conicalGradient);
    }

    else if (style == Qt::TexturePattern)
    {
        paintArea->setBrush(QBrush(QPixmap("butterfly.jpg")));
    }
    else
    {
        paintArea->setBrush(QBrush(color, style));
    }
}

