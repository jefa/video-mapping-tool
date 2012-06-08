/****************************************************************************
** Meta object code from reading C++ file 'processdialog.h'
**
** Created: Sun May 15 12:37:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "processdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProcessDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      31,   14,   14,   14, 0x0a,
      47,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProcessDialog[] = {
    "ProcessDialog\0\0acceptPressed()\0"
    "rejectPressed()\0setOpenFileName()\0"
};

const QMetaObject ProcessDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProcessDialog,
      qt_meta_data_ProcessDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProcessDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProcessDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProcessDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessDialog))
        return static_cast<void*>(const_cast< ProcessDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProcessDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptPressed(); break;
        case 1: rejectPressed(); break;
        case 2: setOpenFileName(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
