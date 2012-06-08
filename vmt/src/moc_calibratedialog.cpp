/****************************************************************************
** Meta object code from reading C++ file 'calibratedialog.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/calibratedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibratedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__CalibrateDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      38,   21,   21,   21, 0x08,
      60,   54,   21,   21, 0x08,
      80,   21,   21,   21, 0x08,
     103,   96,   21,   21, 0x08,
     129,   96,   21,   21, 0x08,
     155,   96,   21,   21, 0x08,
     181,   96,   21,   21, 0x08,
     207,   96,   21,   21, 0x08,
     233,   96,   21,   21, 0x08,
     259,   96,   21,   21, 0x08,
     285,   96,   21,   21, 0x08,
     311,   96,   21,   21, 0x08,
     337,   96,   21,   21, 0x08,
     363,   96,   21,   21, 0x08,
     389,   96,   21,   21, 0x08,
     415,   96,   21,   21, 0x08,
     441,   96,   21,   21, 0x08,
     467,   96,   21,   21, 0x08,
     493,   96,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__CalibrateDialog[] = {
    "gui::CalibrateDialog\0\0acceptPressed()\0"
    "rejectPressed()\0state\0enabledChange(bool)\0"
    "reCalibration()\0newval\0x0IniValueChanged(double)\0"
    "x1IniValueChanged(double)\0"
    "x2IniValueChanged(double)\0"
    "x3IniValueChanged(double)\0"
    "y0IniValueChanged(double)\0"
    "y1IniValueChanged(double)\0"
    "y2IniValueChanged(double)\0"
    "y3IniValueChanged(double)\0"
    "x0FinValueChanged(double)\0"
    "x1FinValueChanged(double)\0"
    "x2FinValueChanged(double)\0"
    "x3FinValueChanged(double)\0"
    "y0FinValueChanged(double)\0"
    "y1FinValueChanged(double)\0"
    "y2FinValueChanged(double)\0"
    "y3FinValueChanged(double)\0"
};

const QMetaObject gui::CalibrateDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__CalibrateDialog,
      qt_meta_data_gui__CalibrateDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::CalibrateDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::CalibrateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::CalibrateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__CalibrateDialog))
        return static_cast<void*>(const_cast< CalibrateDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::CalibrateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptPressed(); break;
        case 1: rejectPressed(); break;
        case 2: enabledChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: reCalibration(); break;
        case 4: x0IniValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: x1IniValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: x2IniValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: x3IniValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: y0IniValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: y1IniValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: y2IniValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: y3IniValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: x0FinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: x1FinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: x2FinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: x3FinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: y0FinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: y1FinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: y2FinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: y3FinValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
