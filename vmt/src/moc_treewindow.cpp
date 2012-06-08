/****************************************************************************
** Meta object code from reading C++ file 'treewindow.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/treewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__TreeWindow[] = {

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
      23,   17,   16,   16, 0x0a,
      50,   16,   16,   16, 0x2a,
      66,   17,   16,   16, 0x0a,
      98,   17,   91,   16, 0x0a,
     119,   16,   16,   16, 0x08,
     145,  138,  133,   16, 0x08,
     171,   16,  133,   16, 0x28,
     186,   16,   16,   16, 0x08,
     198,  138,  133,   16, 0x08,
     224,   16,  133,   16, 0x28,
     239,   16,   16,   16, 0x08,
     251,   16,   16,   16, 0x08,
     264,   16,   16,   16, 0x08,
     275,   16,   16,   16, 0x08,
     286,   16,   16,   16, 0x08,
     301,   16,   16,   16, 0x08,
     315,   16,   16,   16, 0x08,
     330,   16,   16,   16, 0x08,
     344,   16,   16,   16, 0x08,
     361,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__TreeWindow[] = {
    "gui::TreeWindow\0\0index\0"
    "updateActions(QModelIndex)\0updateActions()\0"
    "clickedTree(QModelIndex)\0string\0"
    "ObtType(QModelIndex)\0insertChild()\0"
    "bool\0parent\0insertColumn(QModelIndex)\0"
    "insertColumn()\0insertRow()\0"
    "removeColumn(QModelIndex)\0removeColumn()\0"
    "removeRow()\0editObject()\0saveShow()\0"
    "loadShow()\0setOrbitmode()\0setRollmode()\0"
    "setDollymode()\0setPanymode()\0"
    "setCalibration()\0quit()\0"
};

const QMetaObject gui::TreeWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__TreeWindow,
      qt_meta_data_gui__TreeWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::TreeWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::TreeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::TreeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__TreeWindow))
        return static_cast<void*>(const_cast< TreeWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::TreeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateActions((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: updateActions(); break;
        case 2: clickedTree((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: { string _r = ObtType((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< string*>(_a[0]) = _r; }  break;
        case 4: insertChild(); break;
        case 5: { bool _r = insertColumn((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = insertColumn();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: insertRow(); break;
        case 8: { bool _r = removeColumn((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = removeColumn();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: removeRow(); break;
        case 11: editObject(); break;
        case 12: saveShow(); break;
        case 13: loadShow(); break;
        case 14: setOrbitmode(); break;
        case 15: setRollmode(); break;
        case 16: setDollymode(); break;
        case 17: setPanymode(); break;
        case 18: setCalibration(); break;
        case 19: quit(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
