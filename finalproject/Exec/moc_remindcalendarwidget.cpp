/****************************************************************************
** Meta object code from reading C++ file 'remindcalendarwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../KToDoLists/remindcalendarwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'remindcalendarwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_remindcalendarwidget_t {
    QByteArrayData data[11];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_remindcalendarwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_remindcalendarwidget_t qt_meta_stringdata_remindcalendarwidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "remindcalendarwidget"
QT_MOC_LITERAL(1, 21, 14), // "sendremindtime"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 6), // "retime"
QT_MOC_LITERAL(4, 44, 7), // "retimed"
QT_MOC_LITERAL(5, 52, 25), // "on_calendarWidget_clicked"
QT_MOC_LITERAL(6, 78, 4), // "date"
QT_MOC_LITERAL(7, 83, 27), // "on_timeEdit_userTimeChanged"
QT_MOC_LITERAL(8, 111, 4), // "time"
QT_MOC_LITERAL(9, 116, 24), // "on_pushButton_no_clicked"
QT_MOC_LITERAL(10, 141, 25) // "on_pushButton_yes_clicked"

    },
    "remindcalendarwidget\0sendremindtime\0"
    "\0retime\0retimed\0on_calendarWidget_clicked\0"
    "date\0on_timeEdit_userTimeChanged\0time\0"
    "on_pushButton_no_clicked\0"
    "on_pushButton_yes_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_remindcalendarwidget[] = {

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
    QMetaType::Void, QMetaType::QDate, QMetaType::QTime,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    6,
    QMetaType::Void, QMetaType::QTime,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void remindcalendarwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<remindcalendarwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendremindtime((*reinterpret_cast< QDate(*)>(_a[1])),(*reinterpret_cast< QTime(*)>(_a[2]))); break;
        case 1: _t->on_calendarWidget_clicked((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 2: _t->on_timeEdit_userTimeChanged((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_no_clicked(); break;
        case 4: _t->on_pushButton_yes_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (remindcalendarwidget::*)(QDate , QTime );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&remindcalendarwidget::sendremindtime)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject remindcalendarwidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_remindcalendarwidget.data,
    qt_meta_data_remindcalendarwidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *remindcalendarwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *remindcalendarwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_remindcalendarwidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int remindcalendarwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void remindcalendarwidget::sendremindtime(QDate _t1, QTime _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
