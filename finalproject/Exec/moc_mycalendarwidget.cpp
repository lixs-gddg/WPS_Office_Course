/****************************************************************************
** Meta object code from reading C++ file 'mycalendarwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../KToDoLists/mycalendarwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mycalendarwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mycalenderwidget_t {
    QByteArrayData data[11];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mycalenderwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mycalenderwidget_t qt_meta_stringdata_mycalenderwidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "mycalenderwidget"
QT_MOC_LITERAL(1, 17, 9), // "senddtime"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "dtime"
QT_MOC_LITERAL(4, 34, 6), // "repeat"
QT_MOC_LITERAL(5, 41, 25), // "on_calendarWidget_clicked"
QT_MOC_LITERAL(6, 67, 4), // "date"
QT_MOC_LITERAL(7, 72, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(8, 104, 5), // "index"
QT_MOC_LITERAL(9, 110, 24), // "on_pushButton_no_clicked"
QT_MOC_LITERAL(10, 135, 25) // "on_pushButton_yes_clicked"

    },
    "mycalenderwidget\0senddtime\0\0dtime\0"
    "repeat\0on_calendarWidget_clicked\0date\0"
    "on_comboBox_currentIndexChanged\0index\0"
    "on_pushButton_no_clicked\0"
    "on_pushButton_yes_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mycalenderwidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   44,    2, 0x08 /* Private */,
       7,    1,   47,    2, 0x08 /* Private */,
       9,    0,   50,    2, 0x08 /* Private */,
      10,    0,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QDate, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mycalenderwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mycalenderwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->senddtime((*reinterpret_cast< QDate(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_calendarWidget_clicked((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 2: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_no_clicked(); break;
        case 4: _t->on_pushButton_yes_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (mycalenderwidget::*)(QDate , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mycalenderwidget::senddtime)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mycalenderwidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_mycalenderwidget.data,
    qt_meta_data_mycalenderwidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mycalenderwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mycalenderwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mycalenderwidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int mycalenderwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void mycalenderwidget::senddtime(QDate _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
