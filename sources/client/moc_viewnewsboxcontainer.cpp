/****************************************************************************
** Meta object code from reading C++ file 'viewnewsboxcontainer.h'
**
** Created: Wed Jan 27 01:04:04 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewnewsboxcontainer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewnewsboxcontainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewsClass[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      35,   11,   10,   10, 0x05,
      79,   76,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,   10,   10,   10, 0x0a,
     115,   10,   10,   10, 0x0a,
     137,  133,   10,   10, 0x0a,
     192,  166,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewsClass[] = {
    "NewsClass\0\0id,title,content,cat,me\0"
    "Update(int,QString,QString,int,QWidget*)\0"
    "me\0Deleted(QWidget*)\0OnUpdateAttempt()\0"
    "OnDeleteAttempt()\0how\0"
    "ServerDeleteNewResponse(int)\0"
    "id,title,data,content,cat\0"
    "LoadData(int,QString,QString,QString,int)\0"
};

const QMetaObject NewsClass::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NewsClass,
      qt_meta_data_NewsClass, 0 }
};

const QMetaObject *NewsClass::metaObject() const
{
    return &staticMetaObject;
}

void *NewsClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewsClass))
        return static_cast<void*>(const_cast< NewsClass*>(this));
    return QWidget::qt_metacast(_clname);
}

int NewsClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Update((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QWidget*(*)>(_a[5]))); break;
        case 1: Deleted((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: OnUpdateAttempt(); break;
        case 3: OnDeleteAttempt(); break;
        case 4: ServerDeleteNewResponse((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: LoadData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NewsClass::Update(int _t1, QString _t2, QString _t3, int _t4, QWidget * _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NewsClass::Deleted(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_ViewNewsBoxContainer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      26,   22,   21,   21, 0x0a,
      45,   40,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ViewNewsBoxContainer[] = {
    "ViewNewsBoxContainer\0\0how\0LoadNews(int)\0"
    "news\0DeleteNewsElement(QWidget*)\0"
};

const QMetaObject ViewNewsBoxContainer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewNewsBoxContainer,
      qt_meta_data_ViewNewsBoxContainer, 0 }
};

const QMetaObject *ViewNewsBoxContainer::metaObject() const
{
    return &staticMetaObject;
}

void *ViewNewsBoxContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewNewsBoxContainer))
        return static_cast<void*>(const_cast< ViewNewsBoxContainer*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewNewsBoxContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: LoadNews((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: DeleteNewsElement((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
