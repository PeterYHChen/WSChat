/****************************************************************************
** Meta object code from reading C++ file 'LoginDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WSChat/LoginDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoginDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoginDlg_t {
    QByteArrayData data[8];
    char stringdata[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_LoginDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_LoginDlg_t qt_meta_stringdata_LoginDlg = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 12),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 4),
QT_MOC_LITERAL(4, 28, 16),
QT_MOC_LITERAL(5, 45, 22),
QT_MOC_LITERAL(6, 68, 24),
QT_MOC_LITERAL(7, 93, 17)
    },
    "LoginDlg\0sendUserName\0\0name\0"
    "requestReconnect\0on_loginButton_clicked\0"
    "on_connectButton_clicked\0setDlgSocketState\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x05,
       4,    0,   42,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x08,
       6,    0,   44,    2, 0x08,
       7,    1,   45,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void LoginDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoginDlg *_t = static_cast<LoginDlg *>(_o);
        switch (_id) {
        case 0: _t->sendUserName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->requestReconnect(); break;
        case 2: _t->on_loginButton_clicked(); break;
        case 3: _t->on_connectButton_clicked(); break;
        case 4: _t->setDlgSocketState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LoginDlg::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginDlg::sendUserName)) {
                *result = 0;
            }
        }
        {
            typedef void (LoginDlg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginDlg::requestReconnect)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject LoginDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LoginDlg.data,
      qt_meta_data_LoginDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *LoginDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginDlg.stringdata))
        return static_cast<void*>(const_cast< LoginDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int LoginDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void LoginDlg::sendUserName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LoginDlg::requestReconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
