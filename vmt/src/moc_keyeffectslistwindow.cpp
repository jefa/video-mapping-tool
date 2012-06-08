/****************************************************************************
** Meta object code from reading C++ file 'keyeffectslistwindow.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/keyeffectslistwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyeffectslistwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__keyEffectsListWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x0a,
      50,   44,   26,   26, 0x0a,
      75,   44,   26,   26, 0x0a,
     106,   26,   26,   26, 0x0a,
     118,   26,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gui__keyEffectsListWindow[] = {
    "gui::keyEffectsListWindow\0\0effectsChanged()\0"
    "index\0clickedList(QModelIndex)\0"
    "doubleClickedList(QModelIndex)\0"
    "newEffect()\0removeEffect()\0"
};

const QMetaObject gui::keyEffectsListWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__keyEffectsListWindow,
      qt_meta_data_gui__keyEffectsListWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::keyEffectsListWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::keyEffectsListWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::keyEffectsListWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__keyEffectsListWindow))
        return static_cast<void*>(const_cast< keyEffectsListWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::keyEffectsListWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: effectsChanged(); break;
        case 1: clickedList((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: doubleClickedList((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: newEffect(); break;
        case 4: removeEffect(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
