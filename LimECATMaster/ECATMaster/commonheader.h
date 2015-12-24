#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <QLineEdit>
#include <QString>


#define MAX_SLAVE_LIST  10


#define QSTR_2_CHAR(x)     x.toLocal8Bit().data()

inline void ChangeColorLE(QLineEdit *le, QString cstr){
    le->setStyleSheet("QLineEdit{background:" + cstr + ";}");
}

#endif // COMMONHEADER_H

