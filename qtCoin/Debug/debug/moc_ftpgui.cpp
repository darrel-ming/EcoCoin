/****************************************************************************
** Meta object code from reading C++ file 'ftpgui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/ftp-server/ftpgui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FTPGUI_t {
    QByteArrayData data[12];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FTPGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FTPGUI_t qt_meta_stringdata_FTPGUI = {
    {
QT_MOC_LITERAL(0, 0, 6), // "FTPGUI"
QT_MOC_LITERAL(1, 7, 34), // "on_pushButtonRestartServer_cl..."
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 27), // "on_toolButtonBrowse_clicked"
QT_MOC_LITERAL(4, 71, 15), // "onPeerIpChanged"
QT_MOC_LITERAL(5, 87, 6), // "peerIp"
QT_MOC_LITERAL(6, 94, 33), // "on_pushButtonShowDebugLog_cli..."
QT_MOC_LITERAL(7, 128, 25), // "on_pushButtonExit_clicked"
QT_MOC_LITERAL(8, 154, 21), // "on_adduserbtn_clicked"
QT_MOC_LITERAL(9, 176, 20), // "on_rmuserbtn_clicked"
QT_MOC_LITERAL(10, 197, 23), // "on_savesettings_clicked"
QT_MOC_LITERAL(11, 221, 10) // "writeusers"

    },
    "FTPGUI\0on_pushButtonRestartServer_clicked\0"
    "\0on_toolButtonBrowse_clicked\0"
    "onPeerIpChanged\0peerIp\0"
    "on_pushButtonShowDebugLog_clicked\0"
    "on_pushButtonExit_clicked\0"
    "on_adduserbtn_clicked\0on_rmuserbtn_clicked\0"
    "on_savesettings_clicked\0writeusers"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FTPGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    1,   61,    2, 0x08 /* Private */,
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    0,   68,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FTPGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FTPGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonRestartServer_clicked(); break;
        case 1: _t->on_toolButtonBrowse_clicked(); break;
        case 2: _t->onPeerIpChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_pushButtonShowDebugLog_clicked(); break;
        case 4: _t->on_pushButtonExit_clicked(); break;
        case 5: _t->on_adduserbtn_clicked(); break;
        case 6: _t->on_rmuserbtn_clicked(); break;
        case 7: _t->on_savesettings_clicked(); break;
        case 8: _t->writeusers(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FTPGUI::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_FTPGUI.data,
    qt_meta_data_FTPGUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FTPGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FTPGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FTPGUI.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FTPGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
