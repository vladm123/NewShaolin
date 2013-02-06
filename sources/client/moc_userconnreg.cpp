/****************************************************************************
** Meta object code from reading C++ file 'userconnreg.h'
**
** Created: Wed Jan 27 01:03:50 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "userconnreg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userconnreg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UserConnReg[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      21,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   12,   12,   12, 0x0a,
      56,   12,   12,   12, 0x0a,
      78,   12,   12,   12, 0x0a,
      99,   12,   12,   12, 0x0a,
     125,  121,   12,   12, 0x0a,
     150,  121,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UserConnReg[] = {
    "UserConnReg\0\0id,perm\0User(int,int)\0"
    "onConnectInputEdit()\0onRegisterInputEdit()\0"
    "UserConnectAttempt()\0UserRegisterAttempt()\0"
    "how\0ServerConnectAnswer(int)\0"
    "ServerRegisterAnswer(int)\0"
};

const QMetaObject UserConnReg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UserConnReg,
      qt_meta_data_UserConnReg, 0 }
};

const QMetaObject *UserConnReg::metaObject() const
{
    return &staticMetaObject;
}

void *UserConnReg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserConnReg))
        return static_cast<void*>(const_cast< UserConnReg*>(this));
    return QWidget::qt_metacast(_clname);
}

int UserConnReg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: User((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: onConnectInputEdit(); break;
        case 2: onRegisterInputEdit(); break;
        case 3: UserConnectAttempt(); break;
        case 4: UserRegisterAttempt(); break;
        case 5: ServerConnectAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: ServerRegisterAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void UserConnReg::User(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
