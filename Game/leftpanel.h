#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QProgressBar>

class LeftPanel : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *lPanelLayout;
    QLabel *l_point;
    QLabel *l_level;
    QLabel *l_time;
    QLabel *imageLabel;

    QTimer *countdown;
    int startMilliseconds;

    int pic_id;
    int points;
    int level;

    int perc;

    QProgressBar bar;

public:
    explicit LeftPanel();
    ~LeftPanel();
    void init();
    int getPicId();
    void setPerc(int perc);

signals:
    void updateLevelSignal();
    void restartSignal();
    void updatePercSignal();

public slots:
    void showTime();
    void updatePicture();
    void updatePoint();
    void updateLevel();
    void restart();
    void updatePerc();
};

#endif // LEFTPANEL_H
