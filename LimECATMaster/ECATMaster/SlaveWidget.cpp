#include "SlaveWidget.h"
#include "ui_SlaveWidget.h"

#include <iostream>
#include "commonheader.h"

using namespace std;

SlaveWidget::SlaveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SlaveWidget)
{
    ui->setupUi(this);
    ui->TW_FMMU->setColumnWidth(0, 140);
    ui->TW_FMMU->setColumnWidth(1, 70);
    ui->TW_SM->setColumnWidth(0, 100);
    ui->TW_SM->setColumnWidth(1, 80);

    stateTimer = new QTimer(this);
    connect(stateTimer, SIGNAL(timeout()), this, SLOT(CheckState()));
    stateTimer->start(100);
}

SlaveWidget::~SlaveWidget()
{
    delete ui;
}

void SlaveWidget::CheckState(){
    //ec_readstate();
    WriteStateInfo();
}

void SlaveWidget::WriteStateInfo(){
    QString state;

    switch(slaveInfo->state){
    case 0x01:
        state = "INIT";
        break;
    case 0x02:
        state = "PRE-OP";
        break;
    case 0x03:
        state = "BOOT";
        break;
    case 0x04:
        state = "SAFE-OP";
        break;
    case 0x08:
        state = "OP";
        break;
    case 0x10:
        state = "ERROR";
        break;
    default:
        state = QString().sprintf("?? %2x", slaveInfo->state);
        break;
    }
    ui->LE_STATE->setText(state);
}

void SlaveWidget::UpdatePanel(){
    ui->LB_SLAVE_NAME->setText(QString(slaveInfo->name) + QString().sprintf(" (%d)", slaveNum));
    ui->LE_OUTPUT->setText(QString().sprintf("%d", slaveInfo->Obits));
    ui->LE_INPUT->setText(QString().sprintf("%d", slaveInfo->Ibits));
    WriteStateInfo();
    ui->LE_DELAY->setText(QString().sprintf("%d", slaveInfo->pdelay));
    slaveInfo->hasdc == TRUE ? ui->LE_HASDC->setText("True") : ui->LE_HASDC->setText("False");
    (slaveInfo->activeports & 0x01) > 0 ? ChangeColorLE(ui->LE_ACTIVE_PORT1, "green") : ChangeColorLE(ui->LE_ACTIVE_PORT1, "red");
    (slaveInfo->activeports & 0x02) > 0 ? ChangeColorLE(ui->LE_ACTIVE_PORT2, "green") : ChangeColorLE(ui->LE_ACTIVE_PORT2, "red");
    (slaveInfo->activeports & 0x04) > 0 ? ChangeColorLE(ui->LE_ACTIVE_PORT3, "green") : ChangeColorLE(ui->LE_ACTIVE_PORT3, "red");
    (slaveInfo->activeports & 0x08) > 0 ? ChangeColorLE(ui->LE_ACTIVE_PORT4, "green") : ChangeColorLE(ui->LE_ACTIVE_PORT4, "red");
    ui->LE_CFG_ADDR->setText(QString().sprintf("0x%4.4x", slaveInfo->configadr));
    ui->LE_MANUFACTURER->setText(QString().sprintf("0x%8.8x", slaveInfo->eep_man));
    ui->LE_ID->setText(QString().sprintf("0x%8.8x", slaveInfo->eep_id));
    ui->LE_REVISION->setText(QString().sprintf("0x%8.8x", slaveInfo->eep_rev));
    for(int nSM = 0; nSM < EC_MAXSM; nSM++){
        if(slaveInfo->SM[nSM].StartAddr > 0){
            if(ui->TW_SM->item(nSM, 0) == NULL){
                ui->TW_SM->insertRow(nSM);
                for(int col = 0; col < 4; col++){
                    QTableWidgetItem *newItem = new QTableWidgetItem();
                    ui->TW_SM->setItem(nSM, col, newItem);
                }
            }
            ui->TW_SM->item(nSM, 0)->setText(QString().sprintf("0x%4.4x", slaveInfo->SM[nSM].StartAddr));
            ui->TW_SM->item(nSM, 1)->setText(QString().sprintf("%4d", slaveInfo->SM[nSM].SMlength));
            ui->TW_SM->item(nSM, 2)->setText(QString().sprintf("0x%8.8x", slaveInfo->SM[nSM].SMflags));
            switch(slaveInfo->SMtype[nSM]){
            case 0:
                ui->TW_SM->item(nSM, 3)->setText("Unused");
                break;
            case 1:
                ui->TW_SM->item(nSM, 3)->setText("Mailbox Write");
                break;
            case 2:
                ui->TW_SM->item(nSM, 3)->setText("Mailbox Read");
                break;
            case 3:
                ui->TW_SM->item(nSM, 3)->setText("Outputs");
                break;
            case 4:
                ui->TW_SM->item(nSM, 3)->setText("Inputs");
                break;
            }
        }
    }
    for(int nFMMU = 0; nFMMU < slaveInfo->FMMUunused; nFMMU++){
        if(ui->TW_FMMU->item(nFMMU, 0) == NULL){
            ui->TW_FMMU->insertRow(nFMMU);
            for(int col = 0; col < 5; col++){
                QTableWidgetItem *newItem = new QTableWidgetItem();
                ui->TW_FMMU->setItem(nFMMU, col, newItem);
            }
        }
        ui->TW_FMMU->item(nFMMU, 0)->setText(QString().sprintf("0x%8.8x.%d:%d", slaveInfo->FMMU[nFMMU].LogStart, slaveInfo->FMMU[nFMMU].LogStartbit, slaveInfo->FMMU[nFMMU].LogEndbit));
        ui->TW_FMMU->item(nFMMU, 1)->setText(QString().sprintf("%4d", slaveInfo->FMMU[nFMMU].LogLength));
        ui->TW_FMMU->item(nFMMU, 2)->setText(QString().sprintf("0x%4.4x.%d", slaveInfo->FMMU[nFMMU].PhysStart, slaveInfo->FMMU[nFMMU].PhysStartBit));
        slaveInfo->FMMU[nFMMU].FMMUtype == 0x01 ? ui->TW_FMMU->item(nFMMU, 3)->setText("Input(Read)") : ui->TW_FMMU->item(nFMMU, 3)->setText("Output(Write)");
        slaveInfo->FMMU[nFMMU].FMMUactive == 0x01 ? ui->TW_FMMU->item(nFMMU, 4)->setText("Active") : ui->TW_FMMU->item(nFMMU, 4)->setText("Inactive");
    }

}



