#include "rightpanel.h"
#include "asmopencv.h"

#include <iostream>	// standard C++ I/O
#include <sstream>
#include <QDebug>

using namespace cv; // OpenCV API is in the C++ "cv" namespace
using namespace std;

RightPanel::RightPanel(LeftPanel *lPanel)
{
    this->lPanel = lPanel;
    init();
}

RightPanel::~RightPanel()
{

}

void RightPanel::init()
{
    cap.open(0); // open the video camera no. 0

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
    }

    dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    rng(12345);
    first = 0;

    roi.height = 250;
    roi.width = 250;
//    roi.x = -roi.width/2 + dWidth/2;
//    roi.y = -roi.height/2 + dHeight/2;
    roi.x = dWidth - 250;
    roi.y = 0;

    recta.x = roi.x + 30;
    recta.y = roi.y + 30;
    recta.width = 190;
    recta.height = 190;

    rPanelLayout = new QGridLayout();
    this->setLayout(rPanelLayout);
    rPanelLayout->setSpacing(20);

    l_image = new QLabel();

    timer = new QTimer(this);
    timer->start(50);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateCap()));

    rPanelLayout->addWidget(l_image, 0, 1);

    connect(this, SIGNAL(matched()), lPanel, SLOT(updatePicture()));

    //connect(this, SIGNAL(percSignal()), lPanel, SLOT(updatePerc()));
}

void RightPanel::updateCap()
{
    //cap>>frame;
    cap >> raw;

    if (first == 0)
    {

        first = 1;
        drawfigure = Mat::zeros(raw.size(), CV_8UC3);

        number = lPanel->getPicId();

        name = QString("../../../../images/%1.png").arg(number);
        qDebug() << number;
        qDebug() << name;
        counterimg = imread(name.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
        bitwise_not(counterimg, counterimg);
        flip(counterimg, counterimg, 1);
        vector<vector<Point> > contoursfig;

        vector<Vec4i> hierarchyfig;
        Mat temp;
        temp = counterimg.clone();
        findContours(temp, contoursfig, hierarchyfig, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        //imshow("counter", counterimg);
        /// Draw contours
        Mat figure = Mat::zeros(counterimg.size(), CV_8UC1);
        for (unsigned int i = 0; i< contoursfig.size(); i++)
        {
            drawContours(figure, contoursfig, i, 255, 3, 8, hierarchyfig);
        }

        for (int i = 0; i < figure.cols; i++)
        {
            for (int j = 0; j < figure.rows; j++)
            {
                if (figure.at<uchar>(i, j) == 255)
                {
                    drawfigure.at<Vec3b>(i + 0, j + dWidth-250)[1] = 255;
                }
            }
        }
    }

    flip(raw, raw, 1);
    flip(counterimg, counterimg, 1);
    img = raw.clone();
    //src = img(roi).clone();
    //GaussianBlur(src, src, Size(3, 3), 5);
    cvtColor(img, img, CV_BGR2GRAY);
    Size size(3, 3);
    GaussianBlur(img, img, size, 0);
    Mat gray;
    adaptiveThreshold(img, img, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 75, 10);
    bitwise_not(img, img);

    dst = img(roi).clone();
    // Find contours
    vector<vector<Point> > contours;

    vector<Vec4i> hierarchy;

    findContours(dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    /// Draw contours
    Mat drawing = Mat::zeros(dst.size(), CV_8UC1);
    for (unsigned int i = 0; i< contours.size(); i++)
    {
        double a = contourArea(contours[i], false);
        if (a > countNonZero(counterimg) / 5)
            drawContours(drawing, contours, i, 255, CV_FILLED, 8, hierarchy);
    }

    //Mat counterimg = Mat::zeros(drawing.size(), CV_8UC1);
    Rect shape;
    shape.x = drawing.cols / 2 - 25;
    shape.y = drawing.rows / 2 - 25;
    shape.width = 50;
    shape.height = 50;
    //rectangle(counterimg, shape, 255, CV_FILLED);
    //bitwise_not(counterimg, counterimg);
    int counter = 0;
    for (int i = 0; i < drawing.cols; i++)
    {
        for (int j = 0; j < drawing.rows; j++)
        {
            if (counterimg.at<uchar>(i, j) == 255)
            {
                if (drawing.at<uchar>(i, j) == 255)
                    counter--;
                else
                    counter++;
            }
            else if (drawing.at<uchar>(i, j) != 0)
                counter+=1;
        }
    }

    //PERCENTAGE OF MATCH:
    int perc = 0;
    if (counter<0)
        perc = 100 * (float(abs(counter)) / float(countNonZero(counterimg)));

    lPanel->setPerc(perc);
    //emit(percSignal());

    //BELOW IS THE WIN SIGNAL:
    if (counter < -(countNonZero(counterimg) / 2))
    {
        cout << "You win!" << endl;

        //connect(this, SIGNAL(matched()), lPanel, SLOT(updatePoint()));
        emit matched();

        number = lPanel->getPicId();

        name = QString("../../../../images/%1.png").arg(number);
        qDebug() << number;
        qDebug() << name;
        counterimg = imread(name.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
        bitwise_not(counterimg, counterimg);
        flip(counterimg, counterimg, 1);
        drawfigure = Mat::zeros(drawfigure.size(), CV_8UC3);
        vector<vector<Point> > contoursfig;

        vector<Vec4i> hierarchyfig;
        Mat temp;
        temp = counterimg.clone();
        findContours(temp, contoursfig, hierarchyfig, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        //imshow("counter", counterimg);
        /// Draw contours
        Mat figure = Mat::zeros(counterimg.size(), CV_8UC1);
        for (unsigned int i = 0; i< contoursfig.size(); i++)
        {
            drawContours(figure, contoursfig, i, 255, 3, 8, hierarchyfig);
        }

        for (int i = 0; i < figure.cols; i++)
        {
            for (int j = 0; j < figure.rows; j++)
            {
                if (figure.at<uchar>(i, j) == 255)
                {
                    drawfigure.at<Vec3b>(i + 0, j + dWidth-250)[1] = 255;
                }
            }
        }

    }



    drawing += counterimg;

    //rectangle(raw, recta, Scalar(0, 255, 0));

    rectangle(raw, roi, Scalar(0, 0, 255));
    for(int i=0; i<raw.cols; i++)
    {
        for(int j=0; j<raw.rows; j++)
        {
            if(drawfigure.at<Vec3b>(j,i)[1] == 255)
            {
                raw.at<Vec3b>(j,i)[0] = 0;
                raw.at<Vec3b>(j,i)[1] = 255;
                raw.at<Vec3b>(j,i)[2] = 0;
            }
        }
    }
    //  imshow("drawed", drawing);
    //  imshow("Result window", raw);
    //frame = raw;
    l_image->setPixmap(ASM::cvMatToQPixmap(raw));
}
