QT += testlib
QT += gui
QT += widgets
QT += charts
QT += printsupport

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../rcpsp_qt/algorithm
INCLUDEPATH += ../rcpsp_qt/model

SOURCES +=  tst_basic.cpp \
    ../rcpsp_qt/algorithm/algorithm.cpp \
    ../rcpsp_qt/algorithm/assignedjobs.cpp \
    ../rcpsp_qt/algorithm/completedjobs.cpp \
    ../rcpsp_qt/algorithm/pendingfronts.cpp \
    ../rcpsp_qt/algorithm/pendingjobs.cpp \
    ../rcpsp_qt/contentwidget.cpp \
    ../rcpsp_qt/generator.cpp \
    ../rcpsp_qt/loader.cpp \
    ../rcpsp_qt/mainwindow.cpp \
    ../rcpsp_qt/model/job.cpp \
    ../rcpsp_qt/model/jobgroup.cpp \
    ../rcpsp_qt/model/plan.cpp \
    ../rcpsp_qt/model/worker.cpp \
    ../rcpsp_qt/model/workergroup.cpp \
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
    ../rcpsp_qt/algorithm/algorithm.h \
    ../rcpsp_qt/algorithm/assignedjobs.h \
    ../rcpsp_qt/algorithm/completedjobs.h \
    ../rcpsp_qt/algorithm/pendingfronts.h \
    ../rcpsp_qt/algorithm/pendingjobs.h \
    ../rcpsp_qt/contentwidget.h \
    ../rcpsp_qt/generator.h \
    ../rcpsp_qt/loader.h \
    ../rcpsp_qt/mainwindow.h \
    ../rcpsp_qt/model/job.h \
    ../rcpsp_qt/model/jobgroup.h \
    ../rcpsp_qt/model/plan.h \
    ../rcpsp_qt/model/worker.h \
    ../rcpsp_qt/model/workergroup.h \
    ../rcpsp_qt/plot.h \
    ../rcpsp_qt/qcustomplot.h \
    ../rcpsp_qt/chartview.h \
