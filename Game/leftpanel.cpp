#include "leftpanel.h"
#include <QString>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QFormLayout>
#include <QFont>

LeftPanel::LeftPanel()
{
    pic_id = 1;
    points = 0;
    level = 1;
    startMilliseconds = 20*1000;
    perc = 0;
    init();
}

LeftPanel::~LeftPanel()
{

}

void LeftPanel::init()
{
    QFont font( "Arial", 20, QFont::Bold);
    //font.setPointSize(72);
    //font.setBold(true);

    lPanelLayout = new QGridLayout();
    this->setLayout(lPanelLayout);
    lPanelLayout->setSpacing(20);
    QLabel *pLabel = new QLabel("Point: ");
    pLabel->setFont(font);
    lPanelLayout->addWidget(pLabel, 0, 0);
    l_point = new QLabel("0");
    l_point->setFont(font);
    lPanelLayout->addWidget(l_point, 0, 1);

    QLabel *lLabel = new QLabel("Level: ");
    lLabel->setFont(font);
    lPanelLayout->addWidget(lLabel, 1, 0);
    l_level = new QLabel("1");
    l_level->setFont(font);
    lPanelLayout->addWidget(l_level, 1, 1);

    QLabel *tLabel = new QLabel("Time: ");
    tLabel->setFont(font);
    lPanelLayout->addWidget(tLabel, 2, 0);
    l_time = new QLabel(QString::number(startMilliseconds));
    l_time->setFont(font);
    lPanelLayout->addWidget(l_time, 2, 1);

    countdown = new QTimer(this);
    countdown->setInterval(1000);
    countdown->setSingleShot(false);

    //startMilliseconds = QString(l_time->text()).toInt() * 1000;

    //QTimer *timer = new QTimer(this);
    connect(countdown, SIGNAL(timeout()), this, SLOT(showTime()));
    countdown->start();

    imageLabel = new QLabel();

    imageLabel->setPixmap(QPixmap("../../../../images/1.png"));

    lPanelLayout->addWidget(imageLabel,4,0);

    //bar(0);
    bar.setRange(0,50);
    bar.setValue(0);
    bar.setMinimumWidth(200);

    QWidget *dummyWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("", &bar);

    dummyWidget->setLayout(formLayout);
    lPanelLayout->addWidget(dummyWidget, 3, 0);

    connect(this, SIGNAL(updatePercSignal()), this, SLOT(updatePerc()));

    connect(this, SIGNAL(updateLevelSignal()), this, SLOT(updateLevel()));
    connect(this, SIGNAL(restartSignal()), this, SLOT(restart()));
}

void LeftPanel::showTime()
{
    int seconds;
    if(startMilliseconds - 1000 >= 0)
    {
        startMilliseconds -= 1000;
        seconds = ((startMilliseconds % (1000*60*60)) % (1000*60)) / 1000;
        l_time->setText(QString::number(seconds));

        if(startMilliseconds <= 0)
        {
            countdown->stop();

            QMessageBox msgBox;
            msgBox.setText("Time out, game over!");
            //QPushButton *restartButton = msgBox.addButton(tr("Restart"), QMessageBox::ActionRole);
            QPushButton *abortButton = msgBox.addButton(QMessageBox::Close);

            msgBox.exec();

            /*if (msgBox.clickedButton() == restartButton) {
                emit restartSignal();
            } else*/
            if (msgBox.clickedButton() == abortButton) {
                this->parentWidget()->close();
            }
        }
    }
    else
    {
        countdown->stop();

        QMessageBox msgBox;
        msgBox.setText("Time out, game over!");
        //QPushButton *restartButton = msgBox.addButton(tr("Restart"), QMessageBox::ActionRole);
        QPushButton *abortButton = msgBox.addButton(QMessageBox::Close);

        msgBox.exec();

        /*if (msgBox.clickedButton() == restartButton) {
            emit restartSignal();
        } else */
        if (msgBox.clickedButton() == abortButton) {
            this->parentWidget()->close();
        }

    }
}

void LeftPanel::updatePicture()
{
    if(pic_id != 20)
    {
        pic_id++;
        imageLabel->setPixmap(QPixmap(QString("../../../../images/%1.png").arg(pic_id)));
        points += 10;
        l_point->setText(QString::number(points));

        countdown->stop();
        l_time->setText("20");
        startMilliseconds = 20*1000;
        countdown->start();

        level = pic_id / 5 + 1;

        emit updateLevelSignal();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Congratulations, you made it!");
        QPushButton *abortButton = msgBox.addButton(QMessageBox::Close);

        msgBox.exec();

        if (msgBox.clickedButton() == abortButton) {
            this->parentWidget()->close();
        }
    }
}

void LeftPanel::updatePoint()
{
    points += 10;
    l_point->setText(QString::number(points));
}

void LeftPanel::updateLevel()
{
    l_level->setText(QString::number(level));
}

int LeftPanel::getPicId()
{
    return this->pic_id;
}

void LeftPanel::restart()
{
    pic_id = 1;
    points = 0;
    level = 1;
    startMilliseconds = 20*1000;
}

void LeftPanel::setPerc(int perc)
{
    this->perc = perc;
    emit(updatePercSignal());
}

void LeftPanel::updatePerc()
{
    bar.setValue(perc);
}
