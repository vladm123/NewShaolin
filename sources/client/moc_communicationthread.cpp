/****************************************************************************
** Meta object code from reading C++ file 'communicationthread.h'
**
** Created: Wed Jan 27 01:03:57 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "communicationthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'communicationthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CommunicationThread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CommunicationThread[] = {
    "CommunicationThread\0\0Over(int)\0"
};

const QMetaObject CommunicationThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CommunicationThread,
      qt_meta_data_CommunicationThread, 0 }
};

const QMetaObject *CommunicationThread::metaObject() const
{
    return &staticMetaObject;
}

void *CommunicationThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CommunicationThread))
        return static_cast<void*>(const_cast< CommunicationThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CommunicationThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Over((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CommunicationThread::Over(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
