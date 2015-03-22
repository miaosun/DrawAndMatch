#include "mainwindow.h"
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    lPanel = new LeftPanel();
    rPanel = new RightPanel(lPanel);

    mainLayout->addWidget(lPanel);

    //
    // line seperator
    //
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(line);
    //
    // end line separator
    //

    mainLayout->addWidget(rPanel);

    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    this->setLayout(mainLayout);
    this->setWindowTitle("Draw & Match");

}
