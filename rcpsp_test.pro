QT += testlib
QT += gui
QT += widgets
QT += charts
QT += printsupport

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_basic.cpp \
    ../rcpsp_qt/algorithm.cpp \
    ../rcpsp_qt/chartview.cpp \
    ../rcpsp_qt/contentwidget.cpp \
    ../rcpsp_qt/generator.cpp \
    ../rcpsp_qt/job.cpp \
    ../rcpsp_qt/jobgroup.cpp \
    ../rcpsp_qt/mainwindow.cpp \
    ../rcpsp_qt/plan.cpp \
    ../rcpsp_qt/plot.cpp \
    ../rcpsp_qt/qcustomplot.cpp \
    ../rcpsp_qt/worker.cpp \
    ../rcpsp_qt/workergroup.cpp \
    ../rcpsp_qt/loader.cpp

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
    ../rcpsp_qt/algorithm.h \
    ../rcpsp_qt/chartview.h \
    ../rcpsp_qt/contentwidget.h \
    ../rcpsp_qt/generator.h \
    ../rcpsp_qt/job.h \
    ../rcpsp_qt/jobgroup.h \
    ../rcpsp_qt/mainwindow.h \
    ../rcpsp_qt/plan.h \
    ../rcpsp_qt/plot.h \
    ../rcpsp_qt/qcustomplot.h \
    ../rcpsp_qt/worker.h \
    ../rcpsp_qt/workergroup.h
