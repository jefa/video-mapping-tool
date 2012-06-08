/****************************************************************************
** Meta object code from reading C++ file 'effectpages.h'
**
** Created: Fri Jan 13 02:30:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/effectpages.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'effectpages.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FadeEffectPage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      30,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FadeEffectPage[] = {
    "FadeEffectPage\0\0setColorIni()\0"
    "setColorFin()\0"
};

const QMetaObject FadeEffectPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FadeEffectPage,
      qt_meta_data_FadeEffectPage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FadeEffectPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FadeEffectPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FadeEffectPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FadeEffectPage))
        return static_cast<void*>(const_cast< FadeEffectPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int FadeEffectPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setColorIni(); break;
        case 1: setColorFin(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_TextureEffectPage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      37,   18,   18,   18, 0x0a,
      68,   18,   18,   18, 0x0a,
      99,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TextureEffectPage[] = {
    "TextureEffectPage\0\0setOpenFileName()\0"
    "checkboxGroupStateChanged(int)\0"
    "checkboxVideoStateChanged(int)\0"
    "comboObjectsChanged(int)\0"
};

const QMetaObject TextureEffectPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TextureEffectPage,
      qt_meta_data_TextureEffectPage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextureEffectPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextureEffectPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextureEffectPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextureEffectPage))
        return static_cast<void*>(const_cast< TextureEffectPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int TextureEffectPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setOpenFileName(); break;
        case 1: checkboxGroupStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: checkboxVideoStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: comboObjectsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
