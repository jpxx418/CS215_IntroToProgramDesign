/****************************************************************************
** Meta object code from reading C++ file 'mainForm.h'
**
** Created: Sun Apr 1 01:06:34 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainForm[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      27,    9,    9,    9, 0x0a,
      44,    9,    9,    9, 0x0a,
      58,    9,    9,    9, 0x0a,
      72,    9,    9,    9, 0x0a,
      87,    9,    9,    9, 0x0a,
     103,    9,    9,    9, 0x0a,
     117,    9,    9,    9, 0x0a,
     133,    9,    9,    9, 0x0a,
     148,    9,    9,    9, 0x0a,
     172,  162,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainForm[] = {
    "mainForm\0\0openFileDialog()\0saveFileDialog()\0"
    "shrinkImage()\0increaseRed()\0increaseBlue()\0"
    "increaseGreen()\0decreaseRed()\0"
    "decreaseGreen()\0decreaseBlue()\0"
    "invertImage()\0newString\0updateSizeInfo(QString)\0"
};

const QMetaObject mainForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_mainForm,
      qt_meta_data_mainForm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainForm))
        return static_cast<void*>(const_cast< mainForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int mainForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openFileDialog(); break;
        case 1: saveFileDialog(); break;
        case 2: shrinkImage(); break;
        case 3: increaseRed(); break;
        case 4: increaseBlue(); break;
        case 5: increaseGreen(); break;
        case 6: decreaseRed(); break;
        case 7: decreaseGreen(); break;
        case 8: decreaseBlue(); break;
        case 9: invertImage(); break;
        case 10: updateSizeInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
