/****************************************************************************
** Meta object code from reading C++ file 'midieffecteditdialog.h'
**
** Created: Thu 26. Jan 20:35:51 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/midieffecteditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'midieffecteditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__midiEffecteditdialog[] = {

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
      27,   26,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   26,   26,   26, 0x08,
      57,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__midiEffecteditdialog[] = {
    "gui::midiEffecteditdialog\0\0dataChanged()\0"
    "acceptPressed()\0rejectPressed()\0"
};

const QMetaObject gui::midiEffecteditdialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__midiEffecteditdialog,
      qt_meta_data_gui__midiEffecteditdialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::midiEffecteditdialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::midiEffecteditdialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::midiEffecteditdialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__midiEffecteditdialog))
        return static_cast<void*>(const_cast< midiEffecteditdialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::midiEffecteditdialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataChanged(); break;
        case 1: acceptPressed(); break;
        case 2: rejectPressed(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void gui::midiEffecteditdialog::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
