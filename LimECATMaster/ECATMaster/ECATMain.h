#ifndef ECATMAIN_H
#define ECATMAIN_H

#include <QMainWindow>
#include <SlaveWidget.h>
#include "commonheader.h"


namespace Ui {
class ECATMain;
}

class ECATMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit ECATMain(QWidget *parent = 0);
    ~ECATMain();

private slots:
    void on_BTN_SCAN_clicked();
    void on_BTN_OP_MODE_clicked();
    void on_BTN_DATA_EXCHANGE_clicked();

    void    DataExchange();

private:
    Ui::ECATMain    *ui;
    QTimer          *dataTimer;

    SlaveWidget     *SlaveList[MAX_SLAVE_LIST];


    void    ClearSlaveTabs();

    int     si_map_sdo(int slave);
    int     si_PDOassign(uint16 slave, uint16 PDOassign, int mapoffset, int bitoffset);
    char*   dtype2string(uint16 dtype);

};

#endif // ECATMAIN_H
