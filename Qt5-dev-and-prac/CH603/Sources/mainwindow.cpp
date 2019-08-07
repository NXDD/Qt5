#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)                    //建立主界面，以及初始化默认color，width，style
{
    drawWidget = new DrawWidget;
    setCentralWidget(drawWidget);
    createToolBar();
    setMinimumSize(600, 400);
    ShowStyle();
    drawWidget->setWidth(widthSpinBox->value());
    drawWidget->setColor(Qt::black);       //默认为黑色按钮
}

MainWindow::~MainWindow()
{

}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tool");

    styleLabel = new QLabel(tr("线型风格：")); //线型风格
    styleComboBox = new QComboBox;
    styleComboBox->addItem(tr("SolidLine"), static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));
    styleComboBox->addItem(tr("DotLine"), static_cast<int>(Qt::DotLine));
    styleComboBox->addItem(tr("DashDotLine"), static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem(tr("DashDotDotLine"), static_cast<int>(Qt::DashDotDotLine));
    connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(ShowStyle()));

    widthLabel = new QLabel(tr("线宽："));    //线宽
    widthSpinBox = new QSpinBox;
    connect(widthSpinBox, SIGNAL(valueChanged(int)), drawWidget, SLOT(setWidth(int)));

    colorBtn = new QToolButton;             //颜色按钮
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::black);
    colorBtn->setIcon(QIcon(pixmap));
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(ShowColor()));

    clearBtn = new QToolButton();           //清除btn
    clearBtn->setText(tr("清除："));
    connect(clearBtn, SIGNAL(clicked()), drawWidget, SLOT(clear()));

    //从左至右添加工具栏内容
    toolBar->addWidget(styleLabel);
    toolBar->addWidget(styleComboBox);
    toolBar->addWidget(widthLabel);
    toolBar->addWidget(widthSpinBox);
    toolBar->addWidget(colorBtn);
    toolBar->addWidget(clearBtn);
}

void MainWindow::ShowStyle()                //绘图板取得当前的图线style
{
    drawWidget->setStyle(styleComboBox->itemData(styleComboBox->currentIndex(), Qt::UserRole).toInt());
}

void MainWindow::ShowColor()                //绘图板取得当前color，并将colorBtn显示为当前颜色
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black), this);
    if(color.isValid())
    {
        drawWidget->setColor(color);
        QPixmap p(20, 20); //小正方形，显示颜色
        p.fill(color);
        colorBtn->setIcon(QIcon(p));//colorBtn无文字，仅有一个icon
    }
}
