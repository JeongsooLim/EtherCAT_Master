#ifndef SLAVEWIDGET_H
#define SLAVEWIDGET_H

#include <QWidget>
#include <QTimer>

#include "ethercattype.h"
#include "nicdrv.h"
#include "ethercatbase.h"
#include "ethercatmain.h"
#include "ethercatdc.h"
#include "ethercatcoe.h"
#include "ethercatfoe.h"
#include "ethercatconfig.h"
#include "ethercatprint.h"

namespace Ui {
class SlaveWidget;
}

class SlaveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SlaveWidget(QWidget *parent = 0);
    ~SlaveWidget();

    void    LinkSlaveInfo(ec_slavet *info)  {slaveInfo = info;}
    void    SetSlaveNum(int num)            {slaveNum = num;}

    void    UpdatePanel();


private slots:
    void    CheckState();

private:
    Ui::SlaveWidget *ui;
    QTimer          *stateTimer;

    int             slaveNum;
    ec_slavet       *slaveInfo;


    void    WriteStateInfo();
};

#endif // SLAVEWIDGET_H
