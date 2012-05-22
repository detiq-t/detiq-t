/****************************************************************************
** Meta object code from reading C++ file 'StructElemWindow.h'
**
** Created: Tue May 22 16:26:03 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Widgets/StructElemWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StructElemWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StructElemWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      29,   17,   17,   17, 0x0a,
      40,   17,   17,   17, 0x0a,
      50,   45,   17,   17, 0x0a,
      62,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StructElemWindow[] = {
    "StructElemWindow\0\0openFile()\0saveFile()\0"
    "ok()\0size\0resize(int)\0diamond()\0"
};

void StructElemWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StructElemWindow *_t = static_cast<StructElemWindow *>(_o);
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->saveFile(); break;
        case 2: _t->ok(); break;
        case 3: _t->resize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->diamond(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StructElemWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StructElemWindow::staticMetaObject = {
    { &QMdiSubWindow::staticMetaObject, qt_meta_stringdata_StructElemWindow,
      qt_meta_data_StructElemWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StructElemWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StructElemWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StructElemWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StructElemWindow))
        return static_cast<void*>(const_cast< StructElemWindow*>(this));
    return QMdiSubWindow::qt_metacast(_clname);
}

int StructElemWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMdiSubWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
