/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PA2Layout[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      31,   27,   10,   10, 0x08,
      48,   10,   10,   10, 0x08,
      55,   10,   10,   10, 0x08,
      69,   67,   10,   10, 0x08,
      84,   82,   10,   10, 0x08,
      97,   10,   10,   10, 0x08,
     107,   10,   10,   10, 0x08,
     119,   10,   10,   10, 0x08,
     130,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PA2Layout[] = {
    "PA2Layout\0\0searchClicked()\0pos\0"
    "prodReviews(int)\0save()\0addToCart()\0"
    "p\0userPos(int)\0m\0prodPos(int)\0PopOpen()\0"
    "addReview()\0nameSort()\0rateSort()\0"
};

void PA2Layout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PA2Layout *_t = static_cast<PA2Layout *>(_o);
        switch (_id) {
        case 0: _t->searchClicked(); break;
        case 1: _t->prodReviews((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->save(); break;
        case 3: _t->addToCart(); break;
        case 4: _t->userPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->prodPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->PopOpen(); break;
        case 7: _t->addReview(); break;
        case 8: _t->nameSort(); break;
        case 9: _t->rateSort(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PA2Layout::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PA2Layout::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PA2Layout,
      qt_meta_data_PA2Layout, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PA2Layout::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PA2Layout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PA2Layout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PA2Layout))
        return static_cast<void*>(const_cast< PA2Layout*>(this));
    return QWidget::qt_metacast(_clname);
}

int PA2Layout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
