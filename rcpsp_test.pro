QT += testlib
QT += gui
QT += widgets
QT += charts
QT += printsupport

QMAKE_CXXFLAGS -= -O1
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS -= -O3
QMAKE_CXXFLAGS += -O0

QMAKE_CFLAGS -= -O1
QMAKE_CFLAGS -= -O2
QMAKE_CFLAGS -= -O3
QMAKE_CFLAGS += -O0

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../rcpsp_qt/algorithm
INCLUDEPATH += ../rcpsp_qt/model

SOURCES +=  tst_basic.cpp \
    $$files(../rcpsp_qt/algorithm/*.cpp, true) \
    #../rcpsp_qt/algorithm/assignedjobs.cpp \
    #../rcpsp_qt/algorithm/completedjobs.cpp \
    #../rcpsp_qt/algorithm/pendingfronts.cpp \
    #../rcpsp_qt/algorithm/pendingjobs.cpp \
    ../rcpsp_qt/contentwidget.cpp \
    ../rcpsp_qt/generator.cpp \
    #../rcpsp_qt/loader.cpp \
    ../rcpsp_qt/mainwindow.cpp \
    $$files(../rcpsp_qt/model/*.cpp, true) \
    #../rcpsp_qt/model/jobgroup.cpp \
    #../rcpsp_qt/model/plan.cpp \
    #../rcpsp_qt/model/worker.cpp \
    #../rcpsp_qt/model/workergroup.cpp \
    ../rcpsp_qt/plot.cpp \
    ../rcpsp_qt/qcustomplot.cpp \
    ../rcpsp_qt/chartview.cpp \

SUBDIRS += \
    ../rcpsp_qt/plot_test.pro \
    ../rcpsp_qt/plot_test.pro

FORMS += \
    ../rcpsp_qt/mainwindow.ui

DISTFILES += \
    ../rcpsp_qt/README.md \
    ../rcpsp_qt/generated.csv \
    ../rcpsp_qt/plot_test \
    ../rcpsp_qt/plot_test.pro.user

INCLUDEPATH += ../rcpsp_qt

HEADERS += \
    $$files(../rcpsp_qt/algorithm/*.h, true) \
    #../rcpsp_qt/algorithm/assignedjobs.h \
    #../rcpsp_qt/algorithm/completedjobs.h \
    #../rcpsp_qt/algorithm/pendingfronts.h \
    #../rcpsp_qt/algorithm/pendingjobs.h \
    ../rcpsp_qt/contentwidget.h \
    ../rcpsp_qt/generator.h \
    #../rcpsp_qt/loader.h \
    ../rcpsp_qt/mainwindow.h \
    $$files(../rcpsp_qt/model/*.h, true) \
    #../rcpsp_qt/model/jobgroup.h \
    #../rcpsp_qt/model/plan.h \
    #../rcpsp_qt/model/worker.h \
    #../rcpsp_qt/model/workergroup.h \
    ../rcpsp_qt/plot.h \
    ../rcpsp_qt/qcustomplot.h \
    ../rcpsp_qt/chartview.h \
