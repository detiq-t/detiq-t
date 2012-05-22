/****************************************************************************
** Meta object code from reading C++ file 'BasicTools.h'
**
** Created: Tue May 22 16:26:01 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Services/BasicTools.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BasicTools.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_genericinterface__BasicTools[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x0a,
      46,   29,   29,   29, 0x0a,
      63,   29,   29,   29, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_genericinterface__BasicTools[] = {
    "genericinterface::BasicTools\0\0"
    "applyIdentity()\0applyInversion()\0"
    "convertToGrayscale()\0"
};

void genericinterface::BasicTools::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BasicTools *_t = static_cast<BasicTools *>(_o);
        switch (_id) {
        case 0: _t->applyIdentity(); break;
        case 1: _t->applyInversion(); break;
        case 2: _t->convertToGrayscale(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData genericinterface::BasicTools::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject genericinterface::BasicTools::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_genericinterface__BasicTools,
      qt_meta_data_genericinterface__BasicTools, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &genericinterface::BasicTools::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *genericinterface::BasicTools::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *genericinterface::BasicTools::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_genericinterface__BasicTools))
        return static_cast<void*>(const_cast< BasicTools*>(this));
    if (!strcmp(_clname, "Service"))
        return static_cast< Service*>(const_cast< BasicTools*>(this));
    return QObject::qt_metacast(_clname);
}

int genericinterface::BasicTools::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
