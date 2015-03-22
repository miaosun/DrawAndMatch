#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "leftpanel.h"
#include "rightpanel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();

private:
    LeftPanel *lPanel;
    RightPanel *rPanel;
};

#endif // MAINWINDOW_H
