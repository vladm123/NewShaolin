/****************************************************************************
** Meta object code from reading C++ file 'userprivatespace.h'
**
** Created: Wed Jan 27 01:16:03 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "userprivatespace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userprivatespace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UsersViewModifyButton[] = {

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

static const char qt_meta_stringdata_UsersViewModifyButton[] = {
    "UsersViewModifyButton\0"
};

const QMetaObject UsersViewModifyButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_UsersViewModifyButton,
      qt_meta_data_UsersViewModifyButton, 0 }
};

const QMetaObject *UsersViewModifyButton::metaObject() const
{
    return &staticMetaObject;
}

void *UsersViewModifyButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UsersViewModifyButton))
        return static_cast<void*>(const_cast< UsersViewModifyButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int UsersViewModifyButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_UsersViewModifyDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      27,   23,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   22,   22,   22, 0x0a,
      73,   23,   22,   22, 0x0a,
     100,   22,   22,   22, 0x0a,
     120,   23,   22,   22, 0x0a,
     149,   22,   22,   22, 0x0a,
     163,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UsersViewModifyDialog[] = {
    "UsersViewModifyDialog\0\0how\0"
    "UsersSignalModify(int)\0UserViewUsersAttempt()\0"
    "ServerViewUsersAnswer(int)\0"
    "UserModifyAttempt()\0ServerModifyUsersAnswer(int)\0"
    "onInputEdit()\0onCloseDialog()\0"
};

const QMetaObject UsersViewModifyDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UsersViewModifyDialog,
      qt_meta_data_UsersViewModifyDialog, 0 }
};

const QMetaObject *UsersViewModifyDialog::metaObject() const
{
    return &staticMetaObject;
}

void *UsersViewModifyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UsersViewModifyDialog))
        return static_cast<void*>(const_cast< UsersViewModifyDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int UsersViewModifyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UsersSignalModify((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: UserViewUsersAttempt(); break;
        case 2: ServerViewUsersAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: UserModifyAttempt(); break;
        case 4: ServerModifyUsersAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: onInputEdit(); break;
        case 6: onCloseDialog(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void UsersViewModifyDialog::UsersSignalModify(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_AddNewsButton[] = {

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

static const char qt_meta_stringdata_AddNewsButton[] = {
    "AddNewsButton\0"
};

const QMetaObject AddNewsButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_AddNewsButton,
      qt_meta_data_AddNewsButton, 0 }
};

const QMetaObject *AddNewsButton::metaObject() const
{
    return &staticMetaObject;
}

void *AddNewsButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddNewsButton))
        return static_cast<void*>(const_cast< AddNewsButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int AddNewsButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_UserModifyPassDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      26,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   21,   21,   21, 0x0a,
      76,   22,   21,   21, 0x0a,
     104,   21,   21,   21, 0x0a,
     122,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UserModifyPassDialog[] = {
    "UserModifyPassDialog\0\0how\0"
    "UserSignalModifyPass(int)\0"
    "UserModifyPassAttempt()\0"
    "ServerModifyPassAnswer(int)\0"
    "onPassInputEdit()\0onCloseDialog()\0"
};

const QMetaObject UserModifyPassDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UserModifyPassDialog,
      qt_meta_data_UserModifyPassDialog, 0 }
};

const QMetaObject *UserModifyPassDialog::metaObject() const
{
    return &staticMetaObject;
}

void *UserModifyPassDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserModifyPassDialog))
        return static_cast<void*>(const_cast< UserModifyPassDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int UserModifyPassDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UserSignalModifyPass((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: UserModifyPassAttempt(); break;
        case 2: ServerModifyPassAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: onPassInputEdit(); break;
        case 4: onCloseDialog(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void UserModifyPassDialog::UserSignalModifyPass(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_UserAddNewsDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      52,   26,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      93,   18,   18,   18, 0x0a,
     118,  114,   18,   18, 0x0a,
     143,   18,   18,   18, 0x0a,
     161,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UserAddNewsDialog[] = {
    "UserAddNewsDialog\0\0Done()\0"
    "id,title,Date,content,cat\0"
    "Updated(int,QString,QString,QString,int)\0"
    "UserAddNewsAttempt()\0how\0"
    "ServerAddNewsAnswer(int)\0onNewsInputEdit()\0"
    "onCloseDialog()\0"
};

const QMetaObject UserAddNewsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UserAddNewsDialog,
      qt_meta_data_UserAddNewsDialog, 0 }
};

const QMetaObject *UserAddNewsDialog::metaObject() const
{
    return &staticMetaObject;
}

void *UserAddNewsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserAddNewsDialog))
        return static_cast<void*>(const_cast< UserAddNewsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int UserAddNewsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Done(); break;
        case 1: Updated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: UserAddNewsAttempt(); break;
        case 3: ServerAddNewsAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: onNewsInputEdit(); break;
        case 5: onCloseDialog(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void UserAddNewsDialog::Done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UserAddNewsDialog::Updated(int _t1, QString _t2, QString _t3, QString _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_UserPrivateSpace[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x05,
      50,   47,   17,   17, 0x05,
      70,   17,   17,   17, 0x05,
     105,   79,   17,   17, 0x05,
     149,   17,   17,   17, 0x05,
     161,   17,   17,   17, 0x05,
     173,   17,   17,   17, 0x05,
     185,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     197,   17,   17,   17, 0x0a,
     220,   18,   17,   17, 0x0a,
     247,   17,   17,   17, 0x0a,
     269,   79,   17,   17, 0x0a,
     323,   17,   17,   17, 0x0a,
     344,   17,   17,   17, 0x0a,
     365,   17,   17,   17, 0x0a,
     386,   17,   17,   17, 0x0a,
     412,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UserPrivateSpace[] = {
    "UserPrivateSpace\0\0how\0UserSignalDeconnect(int)\0"
    "id\0UserIdModified(int)\0AddNew()\0"
    "id,title,content,cat,from\0"
    "ModifyNew(int,QString,QString,int,QWidget*)\0"
    "AddNewCat()\0ModifyCat()\0RemoveCat()\0"
    "ViewUsers()\0UserDeconnectAttempt()\0"
    "ServerDeconnectAnswer(int)\0"
    "CreateAddNewsDialog()\0"
    "CreateModNewsDialog(int,QString,QString,int,QWidget*)\0"
    "CreateAddCatDialog()\0CreateModCatDialog()\0"
    "CreateDelCatDialog()\0CreateUsersManageDialog()\0"
    "DeleteDialogs()\0"
};

const QMetaObject UserPrivateSpace::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UserPrivateSpace,
      qt_meta_data_UserPrivateSpace, 0 }
};

const QMetaObject *UserPrivateSpace::metaObject() const
{
    return &staticMetaObject;
}

void *UserPrivateSpace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserPrivateSpace))
        return static_cast<void*>(const_cast< UserPrivateSpace*>(this));
    return QWidget::qt_metacast(_clname);
}

int UserPrivateSpace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UserSignalDeconnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: UserIdModified((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: AddNew(); break;
        case 3: ModifyNew((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QWidget*(*)>(_a[5]))); break;
        case 4: AddNewCat(); break;
        case 5: ModifyCat(); break;
        case 6: RemoveCat(); break;
        case 7: ViewUsers(); break;
        case 8: UserDeconnectAttempt(); break;
        case 9: ServerDeconnectAnswer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: CreateAddNewsDialog(); break;
        case 11: CreateModNewsDialog((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QWidget*(*)>(_a[5]))); break;
        case 12: CreateAddCatDialog(); break;
        case 13: CreateModCatDialog(); break;
        case 14: CreateDelCatDialog(); break;
        case 15: CreateUsersManageDialog(); break;
        case 16: DeleteDialogs(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void UserPrivateSpace::UserSignalDeconnect(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UserPrivateSpace::UserIdModified(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UserPrivateSpace::AddNew()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void UserPrivateSpace::ModifyNew(int _t1, QString _t2, QString _t3, int _t4, QWidget * _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UserPrivateSpace::AddNewCat()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void UserPrivateSpace::ModifyCat()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void UserPrivateSpace::RemoveCat()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void UserPrivateSpace::ViewUsers()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE
