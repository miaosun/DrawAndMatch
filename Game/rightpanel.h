#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QString>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

#include "leftpanel.h"

class RightPanel : public QWidget
{
    Q_OBJECT
public:
    explicit RightPanel(LeftPanel *lPanel);
    ~RightPanel();
    void init();

private:
    QGridLayout *rPanelLayout;
    QLabel *l_image;

    cv::Mat frame;
    cv::VideoCapture cap;

    LeftPanel *lPanel;

    QTimer *timer;
    cv::Mat dst;
    cv::Mat raw;
    cv::Mat counterimg;
    cv::Mat drawfigure;

    cv::Mat img;  // image object


    QString name;
    int number;
    int first;

    cv::Rect roi;
    cv::Rect recta;
    cv::RNG rng;

    double dWidth;
    double dHeight;

signals:
    void matched();

public slots:
    void updateCap();
    //void percSignal();
};

#endif // RIGHTPANEL_H
