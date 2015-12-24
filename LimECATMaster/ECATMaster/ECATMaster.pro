#-------------------------------------------------
#
# Project created by QtCreator 2015-12-19T16:29:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ECATMaster
TEMPLATE = app

INCLUDEPATH += ../ECATMaster/osal/linux \
            ../ECATMaster/osal \
            ../ECATMaster/oshw/linux \
            ../ECATMaster/soem

LIBS += -lpthread

SOURCES += main.cpp\
        ECATMain.cpp \
    osal/linux/osal.c \
    oshw/linux/nicdrv.c \
    oshw/linux/oshw.c \
    soem/ethercatbase.c \
    soem/ethercatcoe.c \
    soem/ethercatconfig.c \
    soem/ethercatdc.c \
    soem/ethercatfoe.c \
    soem/ethercatmain.c \
    soem/ethercatprint.c \
    soem/ethercatsoe.c \
    SlaveWidget.cpp

HEADERS  += ECATMain.h \
    osal/linux/osal_defs.h \
    oshw/linux/nicdrv.h \
    oshw/linux/oshw.h \
    soem/ethercatbase.h \
    soem/ethercatcoe.h \
    soem/ethercatconfig.h \
    soem/ethercatconfiglist.h \
    soem/ethercatdc.h \
    soem/ethercatfoe.h \
    soem/ethercatmain.h \
    soem/ethercatprint.h \
    soem/ethercattype.h \
    soem/ethercatsoe.h \
    commonheader.h \
    SlaveWidget.h

FORMS    += ECATMain.ui \
    SlaveWidget.ui
