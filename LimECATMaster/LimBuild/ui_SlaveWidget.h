/********************************************************************************
** Form generated from reading UI file 'SlaveWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLAVEWIDGET_H
#define UI_SLAVEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SlaveWidget
{
public:
    QLabel *LB_SLAVE_NAME;
    QFrame *line;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *LE_OUTPUT;
    QLabel *label_7;
    QLabel *label_6;
    QLineEdit *LE_HASDC;
    QLineEdit *LE_INPUT;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label;
    QLineEdit *LE_DELAY;
    QLineEdit *LE_ACTIVE_PORT1;
    QLineEdit *LE_CFG_ADDR;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_9;
    QLabel *label_4;
    QLineEdit *LE_STATE;
    QLineEdit *LE_ACTIVE_PORT2;
    QLineEdit *LE_ACTIVE_PORT4;
    QLineEdit *LE_ACTIVE_PORT3;
    QLabel *label_10;
    QLineEdit *LE_MANUFACTURER;
    QLineEdit *LE_ID;
    QLineEdit *LE_REVISION;
    QTableWidget *TW_SM;
    QTableWidget *TW_FMMU;

    void setupUi(QWidget *SlaveWidget)
    {
        if (SlaveWidget->objectName().isEmpty())
            SlaveWidget->setObjectName(QStringLiteral("SlaveWidget"));
        SlaveWidget->resize(879, 563);
        LB_SLAVE_NAME = new QLabel(SlaveWidget);
        LB_SLAVE_NAME->setObjectName(QStringLiteral("LB_SLAVE_NAME"));
        LB_SLAVE_NAME->setGeometry(QRect(15, 15, 141, 16));
        QFont font;
        font.setPointSize(12);
        LB_SLAVE_NAME->setFont(font);
        line = new QFrame(SlaveWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 40, 118, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        gridLayoutWidget = new QWidget(SlaveWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 50, 201, 291));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        LE_OUTPUT = new QLineEdit(gridLayoutWidget);
        LE_OUTPUT->setObjectName(QStringLiteral("LE_OUTPUT"));
        LE_OUTPUT->setReadOnly(true);

        gridLayout->addWidget(LE_OUTPUT, 0, 1, 1, 4);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        LE_HASDC = new QLineEdit(gridLayoutWidget);
        LE_HASDC->setObjectName(QStringLiteral("LE_HASDC"));
        LE_HASDC->setReadOnly(true);

        gridLayout->addWidget(LE_HASDC, 4, 1, 1, 4);

        LE_INPUT = new QLineEdit(gridLayoutWidget);
        LE_INPUT->setObjectName(QStringLiteral("LE_INPUT"));
        LE_INPUT->setReadOnly(true);

        gridLayout->addWidget(LE_INPUT, 1, 1, 1, 4);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        LE_DELAY = new QLineEdit(gridLayoutWidget);
        LE_DELAY->setObjectName(QStringLiteral("LE_DELAY"));
        LE_DELAY->setReadOnly(true);

        gridLayout->addWidget(LE_DELAY, 3, 1, 1, 4);

        LE_ACTIVE_PORT1 = new QLineEdit(gridLayoutWidget);
        LE_ACTIVE_PORT1->setObjectName(QStringLiteral("LE_ACTIVE_PORT1"));
        LE_ACTIVE_PORT1->setReadOnly(true);

        gridLayout->addWidget(LE_ACTIVE_PORT1, 5, 1, 1, 1);

        LE_CFG_ADDR = new QLineEdit(gridLayoutWidget);
        LE_CFG_ADDR->setObjectName(QStringLiteral("LE_CFG_ADDR"));
        LE_CFG_ADDR->setReadOnly(true);

        gridLayout->addWidget(LE_CFG_ADDR, 6, 1, 1, 4);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        LE_STATE = new QLineEdit(gridLayoutWidget);
        LE_STATE->setObjectName(QStringLiteral("LE_STATE"));
        LE_STATE->setReadOnly(true);

        gridLayout->addWidget(LE_STATE, 2, 1, 1, 4);

        LE_ACTIVE_PORT2 = new QLineEdit(gridLayoutWidget);
        LE_ACTIVE_PORT2->setObjectName(QStringLiteral("LE_ACTIVE_PORT2"));
        LE_ACTIVE_PORT2->setReadOnly(true);

        gridLayout->addWidget(LE_ACTIVE_PORT2, 5, 2, 1, 1);

        LE_ACTIVE_PORT4 = new QLineEdit(gridLayoutWidget);
        LE_ACTIVE_PORT4->setObjectName(QStringLiteral("LE_ACTIVE_PORT4"));
        LE_ACTIVE_PORT4->setReadOnly(true);

        gridLayout->addWidget(LE_ACTIVE_PORT4, 5, 4, 1, 1);

        LE_ACTIVE_PORT3 = new QLineEdit(gridLayoutWidget);
        LE_ACTIVE_PORT3->setObjectName(QStringLiteral("LE_ACTIVE_PORT3"));
        LE_ACTIVE_PORT3->setReadOnly(true);

        gridLayout->addWidget(LE_ACTIVE_PORT3, 5, 3, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 9, 0, 1, 1);

        LE_MANUFACTURER = new QLineEdit(gridLayoutWidget);
        LE_MANUFACTURER->setObjectName(QStringLiteral("LE_MANUFACTURER"));
        LE_MANUFACTURER->setReadOnly(true);

        gridLayout->addWidget(LE_MANUFACTURER, 7, 1, 1, 4);

        LE_ID = new QLineEdit(gridLayoutWidget);
        LE_ID->setObjectName(QStringLiteral("LE_ID"));
        LE_ID->setReadOnly(true);

        gridLayout->addWidget(LE_ID, 8, 1, 1, 4);

        LE_REVISION = new QLineEdit(gridLayoutWidget);
        LE_REVISION->setObjectName(QStringLiteral("LE_REVISION"));
        LE_REVISION->setReadOnly(true);

        gridLayout->addWidget(LE_REVISION, 9, 1, 1, 4);

        TW_SM = new QTableWidget(SlaveWidget);
        if (TW_SM->columnCount() < 4)
            TW_SM->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TW_SM->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TW_SM->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TW_SM->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TW_SM->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        TW_SM->setObjectName(QStringLiteral("TW_SM"));
        TW_SM->setGeometry(QRect(230, 50, 401, 151));
        TW_FMMU = new QTableWidget(SlaveWidget);
        if (TW_FMMU->columnCount() < 5)
            TW_FMMU->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TW_FMMU->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TW_FMMU->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        TW_FMMU->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        TW_FMMU->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        TW_FMMU->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        TW_FMMU->setObjectName(QStringLiteral("TW_FMMU"));
        TW_FMMU->setGeometry(QRect(230, 210, 531, 131));

        retranslateUi(SlaveWidget);

        QMetaObject::connectSlotsByName(SlaveWidget);
    } // setupUi

    void retranslateUi(QWidget *SlaveWidget)
    {
        SlaveWidget->setWindowTitle(QApplication::translate("SlaveWidget", "Form", 0));
        LB_SLAVE_NAME->setText(QApplication::translate("SlaveWidget", "TextLabel", 0));
        label_7->setText(QApplication::translate("SlaveWidget", "Cfg. Address", 0));
        label_6->setText(QApplication::translate("SlaveWidget", "Active Port", 0));
        label_5->setText(QApplication::translate("SlaveWidget", "Has DC", 0));
        label_8->setText(QApplication::translate("SlaveWidget", "Manufacturer", 0));
        label->setText(QApplication::translate("SlaveWidget", "Output[Bit]", 0));
        label_2->setText(QApplication::translate("SlaveWidget", "Input[Bit]", 0));
        label_3->setText(QApplication::translate("SlaveWidget", "State", 0));
        label_9->setText(QApplication::translate("SlaveWidget", "ID", 0));
        label_4->setText(QApplication::translate("SlaveWidget", "Delay[ns]", 0));
        label_10->setText(QApplication::translate("SlaveWidget", "Revision", 0));
        QTableWidgetItem *___qtablewidgetitem = TW_SM->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SlaveWidget", "Address", 0));
        QTableWidgetItem *___qtablewidgetitem1 = TW_SM->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SlaveWidget", "Length", 0));
        QTableWidgetItem *___qtablewidgetitem2 = TW_SM->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SlaveWidget", "Flag", 0));
        QTableWidgetItem *___qtablewidgetitem3 = TW_SM->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SlaveWidget", "Type", 0));
        QTableWidgetItem *___qtablewidgetitem4 = TW_FMMU->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("SlaveWidget", "Log Addr.sb:eb", 0));
        QTableWidgetItem *___qtablewidgetitem5 = TW_FMMU->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("SlaveWidget", "Length", 0));
        QTableWidgetItem *___qtablewidgetitem6 = TW_FMMU->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("SlaveWidget", "Phy Addr.sb", 0));
        QTableWidgetItem *___qtablewidgetitem7 = TW_FMMU->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("SlaveWidget", "Type", 0));
        QTableWidgetItem *___qtablewidgetitem8 = TW_FMMU->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QApplication::translate("SlaveWidget", "Active", 0));
    } // retranslateUi

};

namespace Ui {
    class SlaveWidget: public Ui_SlaveWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLAVEWIDGET_H
