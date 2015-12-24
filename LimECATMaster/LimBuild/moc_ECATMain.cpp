/****************************************************************************
** Meta object code from reading C++ file 'ECATMain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ECATMaster/ECATMain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ECATMain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ECATMain_t {
    QByteArrayData data[6];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ECATMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ECATMain_t qt_meta_stringdata_ECATMain = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ECATMain"
QT_MOC_LITERAL(1, 9, 19), // "on_BTN_SCAN_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 22), // "on_BTN_OP_MODE_clicked"
QT_MOC_LITERAL(4, 53, 28), // "on_BTN_DATA_EXCHANGE_clicked"
QT_MOC_LITERAL(5, 82, 12) // "DataExchange"

    },
    "ECATMain\0on_BTN_SCAN_clicked\0\0"
    "on_BTN_OP_MODE_clicked\0"
    "on_BTN_DATA_EXCHANGE_clicked\0DataExchange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ECATMain[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ECATMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ECATMain *_t = static_cast<ECATMain *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_BTN_SCAN_clicked(); break;
        case 1: _t->on_BTN_OP_MODE_clicked(); break;
        case 2: _t->on_BTN_DATA_EXCHANGE_clicked(); break;
        case 3: _t->DataExchange(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ECATMain::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ECATMain.data,
      qt_meta_data_ECATMain,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ECATMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ECATMain::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ECATMain.stringdata0))
        return static_cast<void*>(const_cast< ECATMain*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ECATMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
