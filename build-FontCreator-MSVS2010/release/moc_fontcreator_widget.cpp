/****************************************************************************
** Meta object code from reading C++ file 'fontcreator_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FontCreator/src/fontcreator_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fontcreator_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FontCreatorWidget_t {
    QByteArrayData data[16];
    char stringdata[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FontCreatorWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FontCreatorWidget_t qt_meta_stringdata_FontCreatorWidget = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 20),
QT_MOC_LITERAL(2, 39, 0),
QT_MOC_LITERAL(3, 40, 5),
QT_MOC_LITERAL(4, 46, 17),
QT_MOC_LITERAL(5, 64, 9),
QT_MOC_LITERAL(6, 74, 21),
QT_MOC_LITERAL(7, 96, 7),
QT_MOC_LITERAL(8, 104, 20),
QT_MOC_LITERAL(9, 125, 13),
QT_MOC_LITERAL(10, 139, 13),
QT_MOC_LITERAL(11, 153, 12),
QT_MOC_LITERAL(12, 166, 11),
QT_MOC_LITERAL(13, 178, 12),
QT_MOC_LITERAL(14, 191, 14),
QT_MOC_LITERAL(15, 206, 5)
    },
    "FontCreatorWidget\0OnTextureSizeChenged\0"
    "\0index\0OnFontSizeChanged\0font_size\0"
    "OnChangeOutlineEnable\0checked\0"
    "OnChangeOutlineWidth\0outline_width\0"
    "OnTextChanged\0OnClickASCII\0OnClickKana\0"
    "OnClickKanji\0OnScaleChenged\0value\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FontCreatorWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08,
       4,    1,   62,    2, 0x08,
       6,    1,   65,    2, 0x08,
       8,    1,   68,    2, 0x08,
      10,    0,   71,    2, 0x08,
      11,    0,   72,    2, 0x08,
      12,    0,   73,    2, 0x08,
      13,    0,   74,    2, 0x08,
      14,    1,   75,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void FontCreatorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FontCreatorWidget *_t = static_cast<FontCreatorWidget *>(_o);
        switch (_id) {
        case 0: _t->OnTextureSizeChenged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OnFontSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->OnChangeOutlineEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->OnChangeOutlineWidth((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->OnTextChanged(); break;
        case 5: _t->OnClickASCII(); break;
        case 6: _t->OnClickKana(); break;
        case 7: _t->OnClickKanji(); break;
        case 8: _t->OnScaleChenged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FontCreatorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FontCreatorWidget.data,
      qt_meta_data_FontCreatorWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *FontCreatorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FontCreatorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FontCreatorWidget.stringdata))
        return static_cast<void*>(const_cast< FontCreatorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FontCreatorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
