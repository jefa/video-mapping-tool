/****************************************************************************
** Meta object code from reading C++ file 'backgraundeditdialog.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/backgraundeditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backgraundeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__BackgraundEditorDialog[] = {

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
      29,   28,   28,   28, 0x08,
      45,   28,   28,   28, 0x08,
      68,   61,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__BackgraundEditorDialog[] = {
    "gui::BackgraundEditorDialog\0\0"
    "acceptPressed()\0rejectPressed()\0newVal\0"
    "enabledChange(QColor)\0"
};

const QMetaObject gui::BackgraundEditorDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__BackgraundEditorDialog,
      qt_meta_data_gui__BackgraundEditorDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::BackgraundEditorDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::BackgraundEditorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::BackgraundEditorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__BackgraundEditorDialog))
        return static_cast<void*>(const_cast< BackgraundEditorDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::BackgraundEditorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptPressed(); break;
        case 1: rejectPressed(); break;
        case 2: enabledChange((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
