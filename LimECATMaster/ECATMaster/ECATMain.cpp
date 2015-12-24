#include "ECATMain.h"
#include "ui_ECATMain.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "ethercattype.h"
#include "nicdrv.h"
#include "ethercatbase.h"
#include "ethercatmain.h"
#include "ethercatdc.h"
#include "ethercatcoe.h"
#include "ethercatfoe.h"
#include "ethercatconfig.h"
#include "ethercatprint.h"

#include "commonheader.h"

using namespace std;

char IOmap[4096];
ec_ODlistt ODlist;
ec_OElistt OElist;
char hstr[1024];
int     dataExchangeFlag = false;

//OSAL_THREAD_HANDLE  ecatcheckHandle;
pthread_t           ecatcheckHandle;
//OSAL_THREAD_FUNC ecatcheck(void *ptr);
void *ecatcheck(void *ptr);
#define EC_TIMEOUTMON 500


ECATMain::ECATMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ECATMain)
{
    ui->setupUi(this);

    // Delete default tabs
    ClearSlaveTabs();

    for(int i=0; i<MAX_SLAVE_LIST; i++){
        SlaveList[i] = NULL;
    }



    dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(DataExchange()));
    //dataTimer->start(500);


    /* create thread to handle slave error handling in OP */
    osal_thread_create(&ecatcheckHandle, 128000, &ecatcheck, (void*) &ctime);
}

ECATMain::~ECATMain()
{
    delete ui;
}

void ECATMain::on_BTN_SCAN_clicked()
{
    int expectedWKC;
    uint16 ssigen;

    char *ifname = QSTR_2_CHAR(ui->LE_IF_NAME->text());
    if(ec_init(ifname)){
        cout << "ec_init on " << ifname << " succeeded." << endl;
    }

    if(ec_config(FALSE, &IOmap) > 0){
        ec_configdc();
        while(EcatError)
            cout << ec_elist2string();
        cout << ec_slavecount << " slaves found and configured." << endl;
        expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;
        cout << "Calculated workcounter " << expectedWKC << endl;

        /* wait for all slaves to reach SAFE_OP state */
        ec_statecheck(0, EC_STATE_SAFE_OP,  EC_TIMEOUTSTATE * 3);
        if(ec_slave[0].state != EC_STATE_SAFE_OP){
            cout << "Not all slaves reached safe operational state." << endl;
            ec_readstate();
            for(int i = 1; i<=ec_slavecount ; i++){
                if(ec_slave[i].state != EC_STATE_SAFE_OP){
                    printf("Slave %d State=%2x StatusCode=%4x : %s\n",
                           i, ec_slave[i].state, ec_slave[i].ALstatuscode, ec_ALstatuscode2string(ec_slave[i].ALstatuscode));
                }
            }
        }

        ec_readstate();
        for(int cnt = 1 ; cnt <= ec_slavecount ; cnt++)
        {
            if(SlaveList[cnt-1] == NULL){
                SlaveList[cnt-1] = new SlaveWidget();
                SlaveList[cnt-1]->SetSlaveNum(cnt);
                SlaveList[cnt-1]->LinkSlaveInfo(&ec_slave[cnt]);

                ui->TW_SLAVE->addTab(SlaveList[cnt-1], QString(ec_slave[cnt].name));
            }
            SlaveList[cnt-1]->UpdatePanel();

            /* SII general section */
            if(ssigen){
                ec_slave[cnt].CoEdetails = ec_siigetbyte(cnt, ssigen + 0x07);
                ec_slave[cnt].FoEdetails = ec_siigetbyte(cnt, ssigen + 0x08);
                ec_slave[cnt].EoEdetails = ec_siigetbyte(cnt, ssigen + 0x09);
                ec_slave[cnt].SoEdetails = ec_siigetbyte(cnt, ssigen + 0x0a);
                if((ec_siigetbyte(cnt, ssigen + 0x0d) & 0x02) > 0){
                    ec_slave[cnt].blockLRW = 1;
                    ec_slave[0].blockLRW++;
                }
                ec_slave[cnt].Ebuscurrent = ec_siigetbyte(cnt, ssigen + 0x0e);
                ec_slave[cnt].Ebuscurrent += ec_siigetbyte(cnt, ssigen + 0x0f) << 8;
                ec_slave[0].Ebuscurrent += ec_slave[cnt].Ebuscurrent;
            }

            /* PDO mapping according to CoE */
            if(ec_slave[cnt].mbx_proto & 0x04)
                si_map_sdo(cnt);

            cout << endl;
        }
    }
    else
    {
        printf("No slaves found!\n");
    }
}


int ECATMain::si_map_sdo(int slave)
{
    int wkc, rdl;
    int retVal = 0;
    uint8 nSM, iSM, tSM;
    int Tsize, outputs_bo, inputs_bo;
    uint8 SMt_bug_add;

    printf("PDO mapping according to CoE :\n");
    SMt_bug_add = 0;
    outputs_bo = 0;
    inputs_bo = 0;
    rdl = sizeof(nSM); nSM = 0;
    /* read SyncManager Communication Type object count */
    wkc = ec_SDOread(slave, ECT_SDO_SMCOMMTYPE, 0x00, FALSE, &rdl, &nSM, EC_TIMEOUTRXM);
    /* positive result from slave ? */
    if((wkc > 0) && (nSM > 2)){
        /* make nSM equal to number of defined SM */
        nSM--;
        /* limit to maximum number of SM defined, if true the slave can't be configured */
        if(nSM > EC_MAXSM)
            nSM = EC_MAXSM;
        /* iterate for every SM type defined */
        for(iSM = 2 ; iSM <= nSM ; iSM++){
            rdl = sizeof(tSM); tSM = 0;
            /* read SyncManager Communication Type */
            wkc = ec_SDOread(slave, ECT_SDO_SMCOMMTYPE, iSM + 1, FALSE, &rdl, &tSM, EC_TIMEOUTRXM);
            if (wkc > 0)
            {
                if((iSM == 2) && (tSM == 2)){ // SM2 has type 2 == mailbox out, this is a bug in the slave!
                    SMt_bug_add = 1; // try to correct, this works if the types are 0 1 2 3 and should be 1 2 3 4
                    printf("Activated SM type workaround, possible incorrect mapping.\n");
                }
                if(tSM)
                    tSM += SMt_bug_add; // only add if SMt > 0


                if (tSM == 3){ // outputs
                    /* read the assign RXPDO */
                    printf("  SM%1d outputs\n PDO Index     addr b    index: sub bitl data_type    name\n", iSM);
                    Tsize = si_PDOassign(slave, ECT_SDO_PDOASSIGN + iSM, (int)(ec_slave[slave].outputs - (uint8 *)&IOmap[0]), outputs_bo );
                    outputs_bo += Tsize;
                }
                if (tSM == 4){ // inputs
                    /* read the assign TXPDO */
                    printf("  SM%1d inputs\n  PDO Index     addr b    index: sub bitl data_type    name\n", iSM);
                    Tsize = si_PDOassign(slave, ECT_SDO_PDOASSIGN + iSM, (int)(ec_slave[slave].inputs - (uint8 *)&IOmap[0]), inputs_bo );
                    inputs_bo += Tsize;
                }
            }
        }
    }

    /* found some I/O bits ? */
    if((outputs_bo > 0) || (inputs_bo > 0))
        retVal = 1;
    return retVal;
}

/** Read PDO assign structure */
int ECATMain::si_PDOassign(uint16 slave, uint16 PDOassign, int mapoffset, int bitoffset)
{
    uint16 idxloop, nidx, subidxloop, rdat, idx, subidx;
    uint8 subcnt;
    int wkc, bsize = 0, rdl;
    int32 rdat2;
    uint8 bitlen, obj_subidx;
    uint16 obj_idx;
    int abs_offset, abs_bit;

    rdl = sizeof(rdat); rdat = 0;
    /* read PDO assign subindex 0 ( = number of PDO's) */
    wkc = ec_SDOread(slave, PDOassign, 0x00, FALSE, &rdl, &rdat, EC_TIMEOUTRXM);
    rdat = etohs(rdat);
    /* positive result from slave ? */
    if((wkc > 0) && (rdat > 0)){
        /* number of available sub indexes */
        nidx = rdat;
        bsize = 0;
        /* read all PDO's */
        for(idxloop = 1; idxloop <= nidx; idxloop++){
            rdl = sizeof(rdat); rdat = 0;
            /* read PDO assign */
            wkc = ec_SDOread(slave, PDOassign, (uint8)idxloop, FALSE, &rdl, &rdat, EC_TIMEOUTRXM);
            /* result is index of PDO */
            idx = etohl(rdat);
            if(idx > 0){
                rdl = sizeof(subcnt); subcnt = 0;
                /* read number of subindexes of PDO */
                wkc = ec_SDOread(slave, idx, 0x00, FALSE, &rdl, &subcnt, EC_TIMEOUTRXM);
                subidx = subcnt;

                /* for each subindex */
                for(subidxloop = 1; subidxloop <= subidx; subidxloop++){
                    rdl = sizeof(rdat2); rdat2 = 0;
                    /* read SDO that is mapped in PDO */
                    wkc = ec_SDOread(slave, idx, (uint8)subidxloop, FALSE, &rdl, &rdat2, EC_TIMEOUTRXM);
                    rdat2 = etohl(rdat2);

                    /* extract bitlength of SDO */
                    bitlen = LO_BYTE(rdat2);
                    bsize += bitlen;
                    obj_idx = (uint16)(rdat2 >> 16);
                    obj_subidx = (uint8)((rdat2 >> 8) & 0x000000ff);
                    abs_offset = mapoffset + (bitoffset / 8);
                    abs_bit = bitoffset % 8;
                    ODlist.Slave = slave;
                    ODlist.Index[0] = obj_idx;
                    OElist.Entries = 0;
                    wkc = 0;

                    /* read object entry from dictionary if not a filler (0x0000:0x00) */
                    if(obj_idx || obj_subidx)
                        //wkc = ec_readOEsingle(0, obj_subidx, &ODlist, &OElist);
                        wkc = ec_readOE(0, &ODlist, &OElist);

                    for(int eCnt = 1; eCnt <= OElist.Entries; eCnt++){
                        printf("  [0x%4.4X] %d [0x%4.4X.%1d] 0x%4.4X:0x%2.2X 0x%2.2X", idx, subidxloop, abs_offset, abs_bit, obj_idx, obj_subidx, bitlen);
                        if((wkc > 0) && OElist.Entries)
                        {
                            printf(" %-12s %s %d\n", dtype2string(OElist.DataType[obj_subidx]), OElist.Name[obj_subidx], OElist.Entries);
                        }
                        else
                            printf("\n");
                        bitoffset += bitlen;
                    }
                };
            };
        };
    };
    /* return total found bitlength (PDO) */
    return bsize;
}

char* ECATMain::dtype2string(uint16 dtype)
{
    switch(dtype)
    {
    case ECT_BOOLEAN:
        sprintf(hstr, "BOOLEAN");
        break;
    case ECT_INTEGER8:
        sprintf(hstr, "INTEGER8");
        break;
    case ECT_INTEGER16:
        sprintf(hstr, "INTEGER16");
        break;
    case ECT_INTEGER32:
        sprintf(hstr, "INTEGER32");
        break;
    case ECT_INTEGER24:
        sprintf(hstr, "INTEGER24");
        break;
    case ECT_INTEGER64:
        sprintf(hstr, "INTEGER64");
        break;
    case ECT_UNSIGNED8:
        sprintf(hstr, "UNSIGNED8");
        break;
    case ECT_UNSIGNED16:
        sprintf(hstr, "UNSIGNED16");
        break;
    case ECT_UNSIGNED32:
        sprintf(hstr, "UNSIGNED32");
        break;
    case ECT_UNSIGNED24:
        sprintf(hstr, "UNSIGNED24");
        break;
    case ECT_UNSIGNED64:
        sprintf(hstr, "UNSIGNED64");
        break;
    case ECT_REAL32:
        sprintf(hstr, "REAL32");
        break;
    case ECT_REAL64:
        sprintf(hstr, "REAL64");
        break;
    case ECT_BIT1:
        sprintf(hstr, "BIT1");
        break;
    case ECT_BIT2:
        sprintf(hstr, "BIT2");
        break;
    case ECT_BIT3:
        sprintf(hstr, "BIT3");
        break;
    case ECT_BIT4:
        sprintf(hstr, "BIT4");
        break;
    case ECT_BIT5:
        sprintf(hstr, "BIT5");
        break;
    case ECT_BIT6:
        sprintf(hstr, "BIT6");
        break;
    case ECT_BIT7:
        sprintf(hstr, "BIT7");
        break;
    case ECT_BIT8:
        sprintf(hstr, "BIT8");
        break;
    case ECT_VISIBLE_STRING:
        sprintf(hstr, "VISIBLE_STRING");
        break;
    case ECT_OCTET_STRING:
        sprintf(hstr, "OCTET_STRING");
        break;
    default:
        sprintf(hstr, "Type 0x%4.4X", dtype);
    }
    return hstr;
}


void ECATMain::ClearSlaveTabs(){
    for(int iTab = ui->TW_SLAVE->count()-1; iTab >= 0; iTab--){
        ui->TW_SLAVE->removeTab(iTab);
    }
}

void ECATMain::on_BTN_OP_MODE_clicked()
{
    int expectedWKC, chk, wkc;
    boolean inOP, needlf;

    expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;
    ec_slave[0].state = EC_STATE_OPERATIONAL;

    /* send one valid process data to make outputs in slaves happy*/
    ec_send_processdata();
    ec_receive_processdata(EC_TIMEOUTRET);

    /* request OP state for all slaves */
    //    for(int i = 1; i<=ec_slavecount ; i++){
    //        ec_slave[i].state = EC_STATE_OPERATIONAL;
    //    }
    ec_writestate(0);
    chk = 40;


    /* wait for all slaves to reach OP state */
    do{
        ec_send_processdata();
        ec_receive_processdata(EC_TIMEOUTRET);
        ec_statecheck(0, EC_STATE_OPERATIONAL, 50000);
    }while(chk-- && (ec_slave[0].state != EC_STATE_OPERATIONAL));

    if(ec_slave[0].state == EC_STATE_OPERATIONAL){
        cout << endl << "Operational state reached for all slaves." << endl;
        ec_readstate();

        expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;

//        DataExchange();
//        DataExchange();
//        DataExchange();DataExchange();
//        DataExchange();
//        DataExchange();
        /*
        ec_send_processdata();
        wkc = ec_receive_processdata(EC_TIMEOUTRET);
        cout << "working cnt: " << wkc << ", " << expectedWKC << endl;
        if(wkc >= expectedWKC){
            int out1, out2, in1, in2;
            memcpy(&out1, &ec_slave[0].outputs[0], 4);
            memcpy(&out2, &ec_slave[0].outputs[3], 4);
            memcpy(&in1, &ec_slave[0].inputs[0], 4);
            memcpy(&in2, &ec_slave[0].inputs[3], 4);

            cout << "ProcessData == Output: " << out1 << ", " << out2 << "  Input: " << in1 << ", " <<  in2 << "  T: " << ec_DCtime << endl;

            out1 = 1;
            memcpy(&ec_slave[0].outputs[0], &out1, 4);
        }else{
            cout << "working cnt: " << wkc << ", " << expectedWKC << endl;
        }
        */
    }
}

void ECATMain::DataExchange(){
    static int testCnt = 0;
    if(dataExchangeFlag){
        if(ec_slave[0].state == EC_STATE_OPERATIONAL){
            int wkc;
            int expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;

            ec_send_processdata();
            wkc = ec_receive_processdata(EC_TIMEOUTRET);
            cout << "working cnt: " << wkc << ", " << expectedWKC << endl;
            if(true){//wkc >= expectedWKC){
                int out1, out2, in1, in2;
                memcpy(&out1, &ec_slave[0].outputs[0], 4);
                memcpy(&out2, &ec_slave[0].outputs[3], 4);
                memcpy(&in1, &ec_slave[0].inputs[0], 4);
                memcpy(&in2, &ec_slave[0].inputs[3], 4);

                cout << "ProcessData == Output: " << out1 << ", " << out2 << "  Input: " << in1 << ", " <<  in2 << "  T: " << ec_DCtime << endl;

                out1 = testCnt++;
                memcpy(&ec_slave[0].outputs[0], &out1, 4);
            }else{
                cout << "working cnt: " << wkc << ", " << expectedWKC << endl;
            }
        }
    }
}

void ECATMain::on_BTN_DATA_EXCHANGE_clicked()
{
    if(ui->BTN_DATA_EXCHANGE->text() == "Data Exchange Start"){
        dataExchangeFlag = true;
        ui->BTN_DATA_EXCHANGE->setText("Data Exchange Stop");
    }else{
        dataExchangeFlag = false;
        ui->BTN_DATA_EXCHANGE->setText("Data Exchange Start");
    }
}

//OSAL_THREAD_FUNC ecatcheck(void *ptr)
void* ecatcheck(void *ptr)
{
    static int testCnt = 0;
    while(1){
        //if(dataExchangeFlag){
            if(ec_slave[0].state == EC_STATE_OPERATIONAL){
                int wkc;
                int expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;

                ec_send_processdata();
                wkc = ec_receive_processdata(EC_TIMEOUTRET);
                //cout << "working cnt: " << wkc << ", " << expectedWKC << endl;
                if(wkc >= expectedWKC){
                    int out1, out2, in1, in2;
                    memcpy(&out1, &ec_slave[0].outputs[0], 4);
                    memcpy(&out2, &ec_slave[0].outputs[3], 4);
                    memcpy(&in1, &ec_slave[0].inputs[0], 4);
                    memcpy(&in2, &ec_slave[0].inputs[3], 4);

                    cout << "ProcessData == Output: " << out1 << ", " << out2 << "  Input: " << in1 << ", " <<  in2 << "  T: " << ec_DCtime << endl;

                    out1 = testCnt++;
                    memcpy(&ec_slave[0].outputs[0], &out1, 4);
                }else{
                    cout << "working cnt: " << wkc << ", " << expectedWKC << endl;
                }
            }
        //}
        osal_usleep(50*1000);
    }


//    int slave;
//    int expectedWKC;
//    boolean needlf;
//    volatile int wkc;
//    boolean inOP;
//    uint8 currentgroup = 0;

//    while(1){
//        if(inOP && ((wkc < expectedWKC) || ec_group[currentgroup].docheckstate)){
//            if (needlf){
//                needlf = FALSE;
//                printf("\n");
//            }
//            /* one ore more slaves are not responding */
//            ec_group[currentgroup].docheckstate = FALSE;
//            ec_readstate();
//            for(slave = 1; slave <= ec_slavecount; slave++){
//                if ((ec_slave[slave].group == currentgroup) && (ec_slave[slave].state != EC_STATE_OPERATIONAL)){
//                    ec_group[currentgroup].docheckstate = TRUE;
//                    if (ec_slave[slave].state == (EC_STATE_SAFE_OP + EC_STATE_ERROR)){
//                        printf("ERROR : slave %d is in SAFE_OP + ERROR, attempting ack.\n", slave);
//                        ec_slave[slave].state = (EC_STATE_SAFE_OP + EC_STATE_ACK);
//                        ec_writestate(slave);
//                    }else if(ec_slave[slave].state == EC_STATE_SAFE_OP){
//                        printf("WARNING : slave %d is in SAFE_OP, change to OPERATIONAL.\n", slave);
//                        ec_slave[slave].state = EC_STATE_OPERATIONAL;
//                        ec_writestate(slave);
//                    }else if(ec_slave[slave].state > 0){
//                        if (ec_reconfig_slave(slave, EC_TIMEOUTMON)){
//                            ec_slave[slave].islost = FALSE;
//                            printf("MESSAGE : slave %d reconfigured\n",slave);
//                        }
//                    }else if(!ec_slave[slave].islost){
//                        /* re-check state */
//                        ec_statecheck(slave, EC_STATE_OPERATIONAL, EC_TIMEOUTRET);
//                        if(!ec_slave[slave].state){
//                            ec_slave[slave].islost = TRUE;
//                            printf("ERROR : slave %d lost\n",slave);
//                        }
//                    }
//                }
//                if(ec_slave[slave].islost){
//                    if(!ec_slave[slave].state){
//                        if (ec_recover_slave(slave, EC_TIMEOUTMON)){
//                            ec_slave[slave].islost = FALSE;
//                            printf("MESSAGE : slave %d recovered\n",slave);
//                        }
//                    }else{
//                        ec_slave[slave].islost = FALSE;
//                        printf("MESSAGE : slave %d found\n",slave);
//                    }
//                }
//            }
//            if(!ec_group[currentgroup].docheckstate)
//                printf("OK : all slaves resumed OPERATIONAL.\n");
//        }
//        osal_usleep(10000);
//    }
}


