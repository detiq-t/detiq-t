/****************************************************************************
** Meta object code from reading C++ file 'MorphoMatService.h'
**
** Created: Tue May 22 16:26:02 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Services/MorphoMatService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MorphoMatService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_genericinterface__MorphoMatService[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   35,   35,   35, 0x0a,
      53,   35,   35,   35, 0x0a,
      68,   35,   35,   35, 0x0a,
      86,   35,   35,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_genericinterface__MorphoMatService[] = {
    "genericinterface::MorphoMatService\0\0"
    "editStructElem()\0applyErosion()\0"
    "applyDilatation()\0applyGradient()\0"
};

void genericinterface::MorphoMatService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MorphoMatService *_t = static_cast<MorphoMatService *>(_o);
        switch (_id) {
        case 0: _t->editStructElem(); break;
        case 1: _t->applyErosion(); break;
        case 2: _t->applyDilatation(); break;
        case 3: _t->applyGradient(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData genericinterface::MorphoMatService::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject genericinterface::MorphoMatService::staticMetaObject = {
    { &AlgorithmService::staticMetaObject, qt_meta_stringdata_genericinterface__MorphoMatService,
      qt_meta_data_genericinterface__MorphoMatService, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &genericinterface::MorphoMatService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *genericinterface::MorphoMatService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *genericinterface::MorphoMatService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_genericinterface__MorphoMatService))
        return static_cast<void*>(const_cast< MorphoMatService*>(this));
    return AlgorithmService::qt_metacast(_clname);
}

int genericinterface::MorphoMatService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AlgorithmService::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
