/****************************************************************************
** Meta object code from reading C++ file 'quadeditdialog.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/quadeditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quadeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__QuadEditorDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      39,   22,   22,   22, 0x08,
      55,   22,   22,   22, 0x08,
      78,   22,   22,   22, 0x08,
     101,   22,   22,   22, 0x08,
     124,   22,   22,   22, 0x08,
     147,   22,   22,   22, 0x08,
     170,   22,   22,   22, 0x08,
     193,   22,   22,   22, 0x08,
     216,   22,   22,   22, 0x08,
     239,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__QuadEditorDialog[] = {
    "gui::QuadEditorDialog\0\0acceptPressed()\0"
    "rejectPressed()\0x0ValueChanged(double)\0"
    "y0ValueChanged(double)\0x1ValueChanged(double)\0"
    "y1ValueChanged(double)\0x2ValueChanged(double)\0"
    "y2ValueChanged(double)\0x3ValueChanged(double)\0"
    "y3ValueChanged(double)\0enabledChanged(bool)\0"
};

const QMetaObject gui::QuadEditorDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__QuadEditorDialog,
      qt_meta_data_gui__QuadEditorDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::QuadEditorDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::QuadEditorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::QuadEditorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__QuadEditorDialog))
        return static_cast<void*>(const_cast< QuadEditorDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::QuadEditorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptPressed(); break;
        case 1: rejectPressed(); break;
        case 2: x0ValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: y0ValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: x1ValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: y1ValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: x2ValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: y2ValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: x3ValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: y3ValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: enabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
