/****************************************************************************
** Meta object code from reading C++ file 'viewcats.h'
**
** Created: Wed Jan 27 01:03:59 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewcats.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewcats.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ViewCats[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,    9,    9,    9, 0x0a,
      56,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ViewCats[] = {
    "ViewCats\0\0how\0ViewCatsResponse(int)\0"
    "UpdateCatsAttempt()\0ServerUpdateCatsResponse(int)\0"
};

const QMetaObject ViewCats::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewCats,
      qt_meta_data_ViewCats, 0 }
};

const QMetaObject *ViewCats::metaObject() const
{
    return &staticMetaObject;
}

void *ViewCats::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewCats))
        return static_cast<void*>(const_cast< ViewCats*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewCats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ViewCatsResponse((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: UpdateCatsAttempt(); break;
        case 2: ServerUpdateCatsResponse((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ViewCats::ViewCatsResponse(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
