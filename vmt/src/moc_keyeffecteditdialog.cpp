/****************************************************************************
** Meta object code from reading C++ file 'keyeffecteditdialog.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/keyeffecteditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyeffecteditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__keyEffecteditdialog[] = {

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
      26,   25,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   25,   25,   25, 0x08,
      56,   25,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__keyEffecteditdialog[] = {
    "gui::keyEffecteditdialog\0\0dataChanged()\0"
    "acceptPressed()\0rejectPressed()\0"
};

const QMetaObject gui::keyEffecteditdialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__keyEffecteditdialog,
      qt_meta_data_gui__keyEffecteditdialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::keyEffecteditdialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::keyEffecteditdialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::keyEffecteditdialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__keyEffecteditdialog))
        return static_cast<void*>(const_cast< keyEffecteditdialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::keyEffecteditdialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void gui::keyEffecteditdialog::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
