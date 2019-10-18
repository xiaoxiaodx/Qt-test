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
    QByteArrayData data[13];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BarChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BarChart_t qt_meta_stringdata_BarChart = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BarChart"
QT_MOC_LITERAL(1, 9, 27), // "slot_timeout_axisAnnimation"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 28), // "slot_timeout_chartAnnimation"
QT_MOC_LITERAL(4, 67, 20), // "setCoordinateOriginX"
QT_MOC_LITERAL(5, 88, 2), // "cx"
QT_MOC_LITERAL(6, 91, 20), // "setCoordinateOriginY"
QT_MOC_LITERAL(7, 112, 2), // "cy"
QT_MOC_LITERAL(8, 115, 12), // "setUnitScale"
QT_MOC_LITERAL(9, 128, 2), // "tx"
QT_MOC_LITERAL(10, 131, 2), // "ty"
QT_MOC_LITERAL(11, 134, 18), // "startAxisAnimation"
QT_MOC_LITERAL(12, 153, 19) // "startChartAnimation"

    },
    "BarChart\0slot_timeout_axisAnnimation\0"
    "\0slot_timeout_chartAnnimation\0"
    "setCoordinateOriginX\0cx\0setCoordinateOriginY\0"
    "cy\0setUnitScale\0tx\0ty\0startAxisAnimation\0"
    "startChartAnimation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BarChart[] = {

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
      11,    0,   62,    2, 0x02 /* Public */,
      12,    0,   63,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    9,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BarChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BarChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_timeout_axisAnnimation(); break;
        case 1: _t->slot_timeout_chartAnnimation(); break;
        case 2: _t->setCoordinateOriginX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->setCoordinateOriginY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->setUnitScale((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->startAxisAnimation(); break;
        case 6: _t->startChartAnimation(); break;
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
