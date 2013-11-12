/****************************************************************************
** Meta object code from reading C++ file 'QTlsServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WSChat/QWebSocket_files/QTlsServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QTlsServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtWebsocket__QTlsServer_t {
    QByteArrayData data[10];
    char stringdata[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QtWebsocket__QTlsServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QtWebsocket__QTlsServer_t qt_meta_stringdata_QtWebsocket__QTlsServer = {
    {
QT_MOC_LITERAL(0, 0, 23),
QT_MOC_LITERAL(1, 24, 16),
QT_MOC_LITERAL(2, 41, 0),
QT_MOC_LITERAL(3, 42, 11),
QT_MOC_LITERAL(4, 54, 12),
QT_MOC_LITERAL(5, 67, 16),
QT_MOC_LITERAL(6, 84, 16),
QT_MOC_LITERAL(7, 101, 6),
QT_MOC_LITERAL(8, 108, 18),
QT_MOC_LITERAL(9, 127, 4)
    },
    "QtWebsocket::QTlsServer\0newTlsConnection\0"
    "\0QSslSocket*\0serverSocket\0displayTlsErrors\0"
    "QList<QSslError>\0errors\0tlsSocketEncrypted\0"
    "test\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtWebsocket__QTlsServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x0a,
       8,    0,   40,    2, 0x0a,
       9,    0,   41,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtWebsocket::QTlsServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTlsServer *_t = static_cast<QTlsServer *>(_o);
        switch (_id) {
        case 0: _t->newTlsConnection((*reinterpret_cast< QSslSocket*(*)>(_a[1]))); break;
        case 1: _t->displayTlsErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 2: _t->tlsSocketEncrypted(); break;
        case 3: _t->test(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSslSocket* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTlsServer::*_t)(QSslSocket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTlsServer::newTlsConnection)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QtWebsocket::QTlsServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_QtWebsocket__QTlsServer.data,
      qt_meta_data_QtWebsocket__QTlsServer,  qt_static_metacall, 0, 0}
};


const QMetaObject *QtWebsocket::QTlsServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtWebsocket::QTlsServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtWebsocket__QTlsServer.stringdata))
        return static_cast<void*>(const_cast< QTlsServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int QtWebsocket::QTlsServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QtWebsocket::QTlsServer::newTlsConnection(QSslSocket * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
