/****************************************************************************
** Meta object code from reading C++ file 'chartbase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TestChart/chartbase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chartbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChartBase_t {
    QByteArrayData data[14];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChartBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChartBase_t qt_meta_stringdata_ChartBase = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ChartBase"
QT_MOC_LITERAL(1, 10, 27), // "slot_timeout_axisAnnimation"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 28), // "slot_timeout_chartAnnimation"
QT_MOC_LITERAL(4, 68, 20), // "setCoordinateOriginX"
QT_MOC_LITERAL(5, 89, 2), // "cx"
QT_MOC_LITERAL(6, 92, 20), // "setCoordinateOriginY"
QT_MOC_LITERAL(7, 113, 2), // "cy"
QT_MOC_LITERAL(8, 116, 12), // "setUnitScale"
QT_MOC_LITERAL(9, 129, 2), // "tx"
QT_MOC_LITERAL(10, 132, 2), // "ty"
QT_MOC_LITERAL(11, 135, 18), // "startAxisAnimation"
QT_MOC_LITERAL(12, 154, 2), // "ms"
QT_MOC_LITERAL(13, 157, 19) // "startChartAnimation"

    },
    "ChartBase\0slot_timeout_axisAnnimation\0"
    "\0slot_timeout_chartAnnimation\0"
    "setCoordinateOriginX\0cx\0setCoordinateOriginY\0"
    "cy\0setUnitScale\0tx\0ty\0startAxisAnimation\0"
    "ms\0startChartAnimation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChartBase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    1,   51,    2, 0x02 /* Public */,
       6,    1,   54,    2, 0x02 /* Public */,
       8,    2,   57,    2, 0x02 /* Public */,
      11,    1,   62,    2, 0x02 /* Public */,
      13,    1,   65,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void ChartBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChartBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_timeout_axisAnnimation(); break;
        case 1: _t->slot_timeout_chartAnnimation(); break;
        case 2: _t->setCoordinateOriginX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->setCoordinateOriginY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->setUnitScale((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->startAxisAnimation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->startChartAnimation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChartBase::staticMetaObject = { {
    &QQuickPaintedItem::staticMetaObject,
    qt_meta_stringdata_ChartBase.data,
    qt_meta_data_ChartBase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChartBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChartBase.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int ChartBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
