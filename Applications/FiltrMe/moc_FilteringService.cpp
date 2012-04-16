/****************************************************************************
** Meta object code from reading C++ file 'FilteringService.h'
**
** Created: Tue Apr 17 01:26:50 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "FilteringService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FilteringService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_genericinterface__FilteringService[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   35,   35,   35, 0x0a,
      53,   35,   35,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_genericinterface__FilteringService[] = {
    "genericinterface::FilteringService\0\0"
    "applyFiltering()\0apply(imagein::algorithm::Filtering*)\0"
};

const QMetaObject genericinterface::FilteringService::staticMetaObject = {
    { &AlgorithmService::staticMetaObject, qt_meta_stringdata_genericinterface__FilteringService,
      qt_meta_data_genericinterface__FilteringService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &genericinterface::FilteringService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *genericinterface::FilteringService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *genericinterface::FilteringService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_genericinterface__FilteringService))
        return static_cast<void*>(const_cast< FilteringService*>(this));
    return AlgorithmService::qt_metacast(_clname);
}

int genericinterface::FilteringService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AlgorithmService::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: applyFiltering(); break;
        case 1: apply((*reinterpret_cast< imagein::algorithm::Filtering*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
