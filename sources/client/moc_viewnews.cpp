/****************************************************************************
** Meta object code from reading C++ file 'viewnews.h'
**
** Created: Wed Jan 27 01:04:02 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewnews.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewnews.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ViewNews[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,    9,    9,    9, 0x0a,
      59,   10,    9,    9, 0x0a,
      87,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ViewNews[] = {
    "ViewNews\0\0how\0UpdatedGlobalNewsList(int)\0"
    "ViewNewsAttempt()\0ServerViewNewsResponse(int)\0"
    "onInputEdit()\0"
};

const QMetaObject ViewNews::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewNews,
      qt_meta_data_ViewNews, 0 }
};

const QMetaObject *ViewNews::metaObject() const
{
    return &staticMetaObject;
}

void *ViewNews::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewNews))
        return static_cast<void*>(const_cast< ViewNews*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewNews::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UpdatedGlobalNewsList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: ViewNewsAttempt(); break;
        case 2: ServerViewNewsResponse((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: onInputEdit(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ViewNews::UpdatedGlobalNewsList(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
