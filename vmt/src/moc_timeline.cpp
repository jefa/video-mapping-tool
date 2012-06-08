/****************************************************************************
** Meta object code from reading C++ file 'timeline.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/timeline.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timeline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_timeline[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x0a,
      32,    9,    9,    9, 0x0a,
      67,   58,    9,    9, 0x0a,
      98,    9,    9,    9, 0x0a,
     109,    9,    9,    9, 0x0a,
     117,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_timeline[] = {
    "timeline\0\0x\0valueChanged(qreal)\0"
    "frameChangedTimeline(int)\0newState\0"
    "stateChanged(QTimeLine::State)\0"
    "finished()\0start()\0changePositionSlider(int)\0"
};

const QMetaObject timeline::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_timeline,
      qt_meta_data_timeline, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &timeline::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *timeline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *timeline::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_timeline))
        return static_cast<void*>(const_cast< timeline*>(this));
    return QWidget::qt_metacast(_clname);
}

int timeline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: frameChangedTimeline((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: stateChanged((*reinterpret_cast< QTimeLine::State(*)>(_a[1]))); break;
        case 3: finished(); break;
        case 4: start(); break;
        case 5: changePositionSlider((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
