/****************************************************************************
** Meta object code from reading C++ file 'useraddcat.h'
**
** Created: Wed Jan 27 01:04:00 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "useraddcat.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'useraddcat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddCatButton[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_AddCatButton[] = {
    "AddCatButton\0"
};

const QMetaObject AddCatButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_AddCatButton,
      qt_meta_data_AddCatButton, 0 }
};

const QMetaObject *AddCatButton::metaObject() const
{
    return &staticMetaObject;
}

void *AddCatButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddCatButton))
        return static_cast<void*>(const_cast< AddCatButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int AddCatButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ModCatButton[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_ModCatButton[] = {
    "ModCatButton\0"
};

const QMetaObject ModCatButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_ModCatButton,
      qt_meta_data_ModCatButton, 0 }
};

const QMetaObject *ModCatButton::metaObject() const
{
    return &staticMetaObject;
}

void *ModCatButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModCatButton))
        return static_cast<void*>(const_cast< ModCatButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int ModCatButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_DelCatButton[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_DelCatButton[] = {
    "DelCatButton\0"
};

const QMetaObject DelCatButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_DelCatButton,
      qt_meta_data_DelCatButton, 0 }
};

const QMetaObject *DelCatButton::metaObject() const
{
    return &staticMetaObject;
}

void *DelCatButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DelCatButton))
        return static_cast<void*>(const_cast< DelCatButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int DelCatButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_UserAddModCatDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      25,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   20,   20,   20, 0x0a,
      73,   21,   20,   20, 0x0a,
     100,   20,   20,   20, 0x0a,
     114,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UserAddModCatDialog[] = {
    "UserAddModCatDialog\0\0how\0"
    "UserSignalModifyCat(int)\0"
    "UserAddModCatAttempt()\0"
    "ServerAddModCatAnswer(int)\0onInputEdit()\0"
    "onCloseDialog()\0"
};

const QMetaObject UserAddModCatDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UserAddModCatDialog,
      qt_meta_data_UserAddModCatDialog, 0 }
};

const QMetaObject *UserAddModCatDialog::metaObject() const
{
    return &staticMetaObject;
}

void *UserAddModCatDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserAddModCatDialog))
        return static_cast<void*>(const_cast< UserAddModCatDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int UserAddModCatDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UserSignalModifyCat((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: UserAddModCatAttempt(); break;
        case 2: ServerAddModCatAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: onInputEdit(); break;
        case 4: onCloseDialog(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void UserAddModCatDialog::UserSignalModifyCat(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_UserDelCatDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   17,   17,   17, 0x0a,
      64,   18,   17,   17, 0x0a,
      88,   17,   17,   17, 0x0a,
     102,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UserDelCatDialog[] = {
    "UserDelCatDialog\0\0how\0UserSignalDelCat(int)\0"
    "UserDelCatAttempt()\0ServerDelCatAnswer(int)\0"
    "onInputEdit()\0onCloseDialog()\0"
};

const QMetaObject UserDelCatDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UserDelCatDialog,
      qt_meta_data_UserDelCatDialog, 0 }
};

const QMetaObject *UserDelCatDialog::metaObject() const
{
    return &staticMetaObject;
}

void *UserDelCatDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserDelCatDialog))
        return static_cast<void*>(const_cast< UserDelCatDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int UserDelCatDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UserSignalDelCat((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: UserDelCatAttempt(); break;
        case 2: ServerDelCatAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: onInputEdit(); break;
        case 4: onCloseDialog(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void UserDelCatDialog::UserSignalDelCat(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
