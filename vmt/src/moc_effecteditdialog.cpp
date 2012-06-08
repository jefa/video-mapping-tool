/****************************************************************************
** Meta object code from reading C++ file 'effecteditdialog.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/effecteditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'effecteditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EffectEditDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   32,   17,   17, 0x0a,
      95,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EffectEditDialog[] = {
    "EffectEditDialog\0\0dataChanged()\0"
    "current,previous\0"
    "changePage(QListWidgetItem*,QListWidgetItem*)\0"
    "save()\0"
};

const QMetaObject EffectEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EffectEditDialog,
      qt_meta_data_EffectEditDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EffectEditDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EffectEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EffectEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EffectEditDialog))
        return static_cast<void*>(const_cast< EffectEditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int EffectEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataChanged(); break;
        case 1: changePage((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 2: save(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void EffectEditDialog::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
