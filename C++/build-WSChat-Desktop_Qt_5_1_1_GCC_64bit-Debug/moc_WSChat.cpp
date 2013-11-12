/****************************************************************************
** Meta object code from reading C++ file 'WSChat.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WSChat/WSChat.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WSChat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WSChat_t {
    QByteArrayData data[8];
    char stringdata[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_WSChat_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_WSChat_t qt_meta_stringdata_WSChat = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 17),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 22),
QT_MOC_LITERAL(4, 49, 16),
QT_MOC_LITERAL(5, 66, 15),
QT_MOC_LITERAL(6, 82, 12),
QT_MOC_LITERAL(7, 95, 12)
    },
    "WSChat\0setDlgSocketState\0\0"
    "on_enterButton_clicked\0checkSocketState\0"
    "reconnectSocket\0sendUserName\0checkMessage\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WSChat[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    0,   47,    2, 0x08,
       4,    0,   48,    2, 0x08,
       5,    0,   49,    2, 0x08,
       6,    1,   50,    2, 0x08,
       7,    1,   53,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void WSChat::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WSChat *_t = static_cast<WSChat *>(_o);
        switch (_id) {
        case 0: _t->setDlgSocketState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_enterButton_clicked(); break;
        case 2: _t->checkSocketState(); break;
        case 3: _t->reconnectSocket(); break;
        case 4: _t->sendUserName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->checkMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WSChat::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WSChat::setDlgSocketState)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject WSChat::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_WSChat.data,
      qt_meta_data_WSChat,  qt_static_metacall, 0, 0}
};


const QMetaObject *WSChat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WSChat::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WSChat.stringdata))
        return static_cast<void*>(const_cast< WSChat*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int WSChat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WSChat::setDlgSocketState(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
