#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T13:44:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        leftpanel.cpp \
        rightpanel.cpp

HEADERS  += mainwindow.h \
    leftpanel.h \
    rightpanel.h \
    asmopencv.h

FORMS    +=

LIBS += -L/opt/local/lib \
        -lopencv_core.2.4.11 \
        -lopencv_highgui.2.4.11 \
        -lopencv_flann.2.4.11 \
        -lopencv_imgproc.2.4.11 \
        -lopencv_legacy.2.4.11 \
        -lopencv_objdetect.2.4.11 \
        -lopencv_photo.2.4.11 \
        -lopencv_video.2.4.11 \
        -lopencv_ml.2.4.11 \
        -lopencv_nonfree.2.4.11 \
        -lopencv_ocl.2.4.11 \
        -lopencv_stitching.2.4.11 \
        -lopencv_superres.2.4.11 \
        -lopencv_videostab.2.4.11

INCLUDEPATH += /opt/local/include

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10

DISTFILES += \
    images/miao.jpg
