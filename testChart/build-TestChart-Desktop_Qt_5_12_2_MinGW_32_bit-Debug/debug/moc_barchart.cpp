/****************************************************************************
** Meta object code from reading C++ file 'barchart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TestChart/barchart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'barchart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BarChart_t {
    QByteArrayData data[9];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BarChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BarChart_t qt_meta_stringdata_BarChart = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BarChart"
QT_MOC_LITERAL(1, 9, 20), // "setCoordinateOriginX"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 2), // "cx"
QT_MOC_LITERAL(4, 34, 20), // "setCoordinateOriginY"
QT_MOC_LITERAL(5, 55, 2), // "cy"
QT_MOC_LITERAL(6, 58, 12), // "setUnitScale"
QT_MOC_LITERAL(7, 71, 2), // "tx"
QT_MOC_LITERAL(8, 74, 2) // "ty"

    },
    "BarChart\0setCoordinateOriginX\0\0cx\0"
    "setCoordinateOriginY\0cy\0setUnitScale\0"
    "tx\0ty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BarChart[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x02 /* Public */,
       4,    1,   32,    2, 0x02 /* Public */,
       6,    2,   35,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    7,    8,

       0        // eod
};

void BarChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BarChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCoordinateOriginX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->setCoordinateOriginY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->setUnitScale((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BarChart::staticMetaObject = { {
    &QQuickPaintedItem::staticMetaObject,
    qt_meta_stringdata_BarChart.data,
    qt_meta_data_BarChart,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BarChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BarChart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BarChart.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int BarChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
