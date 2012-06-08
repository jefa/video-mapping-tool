/****************************************************************************
** Meta object code from reading C++ file 'cameraeditdialog.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/cameraeditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameraeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__CameraEditorDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,
      41,   24,   24,   24, 0x08,
      57,   24,   24,   24, 0x08,
      79,   24,   24,   24, 0x08,
     101,   24,   24,   24, 0x08,
     123,   24,   24,   24, 0x08,
     148,   24,   24,   24, 0x08,
     173,   24,   24,   24, 0x08,
     198,   24,   24,   24, 0x08,
     222,   24,   24,   24, 0x08,
     246,   24,   24,   24, 0x08,
     270,   24,   24,   24, 0x08,
     302,   24,   24,   24, 0x08,
     334,   24,   24,   24, 0x08,
     360,   24,   24,   24, 0x08,
     391,  385,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__CameraEditorDialog[] = {
    "gui::CameraEditorDialog\0\0acceptPressed()\0"
    "rejectPressed()\0xValueChanged(double)\0"
    "yValueChanged(double)\0zValueChanged(double)\0"
    "xValueChangedEye(double)\0"
    "yValueChangedEye(double)\0"
    "zValueChangedEye(double)\0"
    "xValueChangedUp(double)\0yValueChangedUp(double)\0"
    "zValueChangedUp(double)\0"
    "fieldOfViewValueChanged(double)\0"
    "aspectRatioValueChanged(double)\0"
    "zNearValueChanged(double)\0"
    "zFarValueChanged(double)\0state\0"
    "proyectorChange(bool)\0"
};

const QMetaObject gui::CameraEditorDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__CameraEditorDialog,
      qt_meta_data_gui__CameraEditorDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::CameraEditorDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::CameraEditorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::CameraEditorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__CameraEditorDialog))
        return static_cast<void*>(const_cast< CameraEditorDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::CameraEditorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptPressed(); break;
        case 1: rejectPressed(); break;
        case 2: xValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: yValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: zValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: xValueChangedEye((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: yValueChangedEye((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: zValueChangedEye((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: xValueChangedUp((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: yValueChangedUp((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: zValueChangedUp((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: fieldOfViewValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: aspectRatioValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: zNearValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: zFarValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: proyectorChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
