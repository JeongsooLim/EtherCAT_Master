/********************************************************************************
** Form generated from reading UI file 'ECATMain.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECATMAIN_H
#define UI_ECATMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ECATMain
{
public:
    QWidget *centralWidget;
    QLineEdit *LE_IF_NAME;
    QPushButton *BTN_SCAN;
    QTabWidget *TW_SLAVE;
    QWidget *tab;
    QWidget *tab_2;
    QPushButton *BTN_OP_MODE;
    QPushButton *BTN_DATA_EXCHANGE;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ECATMain)
    {
        if (ECATMain->objectName().isEmpty())
            ECATMain->setObjectName(QStringLiteral("ECATMain"));
        ECATMain->resize(836, 544);
        centralWidget = new QWidget(ECATMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LE_IF_NAME = new QLineEdit(centralWidget);
        LE_IF_NAME->setObjectName(QStringLiteral("LE_IF_NAME"));
        LE_IF_NAME->setGeometry(QRect(10, 10, 51, 23));
        LE_IF_NAME->setLayoutDirection(Qt::LeftToRight);
        LE_IF_NAME->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BTN_SCAN = new QPushButton(centralWidget);
        BTN_SCAN->setObjectName(QStringLiteral("BTN_SCAN"));
        BTN_SCAN->setGeometry(QRect(70, 10, 71, 23));
        TW_SLAVE = new QTabWidget(centralWidget);
        TW_SLAVE->setObjectName(QStringLiteral("TW_SLAVE"));
        TW_SLAVE->setGeometry(QRect(20, 50, 781, 411));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        TW_SLAVE->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        TW_SLAVE->addTab(tab_2, QString());
        BTN_OP_MODE = new QPushButton(centralWidget);
        BTN_OP_MODE->setObjectName(QStringLiteral("BTN_OP_MODE"));
        BTN_OP_MODE->setGeometry(QRect(160, 10, 81, 23));
        BTN_DATA_EXCHANGE = new QPushButton(centralWidget);
        BTN_DATA_EXCHANGE->setObjectName(QStringLiteral("BTN_DATA_EXCHANGE"));
        BTN_DATA_EXCHANGE->setGeometry(QRect(250, 10, 161, 23));
        ECATMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ECATMain);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 836, 20));
        ECATMain->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ECATMain);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ECATMain->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ECATMain);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ECATMain->setStatusBar(statusBar);

        retranslateUi(ECATMain);

        TW_SLAVE->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ECATMain);
    } // setupUi

    void retranslateUi(QMainWindow *ECATMain)
    {
        ECATMain->setWindowTitle(QApplication::translate("ECATMain", "Lim - EtherCAT Master", 0));
        LE_IF_NAME->setText(QApplication::translate("ECATMain", "eth0", 0));
        BTN_SCAN->setText(QApplication::translate("ECATMain", "Scan", 0));
        TW_SLAVE->setTabText(TW_SLAVE->indexOf(tab), QApplication::translate("ECATMain", "Tab 1", 0));
        TW_SLAVE->setTabText(TW_SLAVE->indexOf(tab_2), QApplication::translate("ECATMain", "Tab 2", 0));
        BTN_OP_MODE->setText(QApplication::translate("ECATMain", "OP Mode", 0));
        BTN_DATA_EXCHANGE->setText(QApplication::translate("ECATMain", "Data Exchange Start", 0));
    } // retranslateUi

};

namespace Ui {
    class ECATMain: public Ui_ECATMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECATMAIN_H
