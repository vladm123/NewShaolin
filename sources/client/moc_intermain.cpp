/****************************************************************************
** Meta object code from reading C++ file 'intermain.h'
**
** Created: Wed Jan 27 01:53:24 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "intermain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'intermain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InterMain[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   26,   10,   10, 0x0a,
      68,   60,   10,   10, 0x0a,
     100,   26,   10,   10, 0x0a,
     130,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InterMain[] = {
    "InterMain\0\0AboutToClose()\0how\0"
    "SuccessfullServerConnect(int)\0id,perm\0"
    "SuccessfullUserConnect(int,int)\0"
    "SuccessfullUserDeconnect(int)\0"
    "servershutdown()\0"
};

const QMetaObject InterMain::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_InterMain,
      qt_meta_data_InterMain, 0 }
};

const QMetaObject *InterMain::metaObject() const
{
    return &staticMetaObject;
}

void *InterMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InterMain))
        return static_cast<void*>(const_cast< InterMain*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int InterMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: AboutToClose(); break;
        case 1: SuccessfullServerConnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: SuccessfullUserConnect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: SuccessfullUserDeconnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: servershutdown(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void InterMain::AboutToClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
