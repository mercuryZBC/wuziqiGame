/****************************************************************************
** Meta object code from reading C++ file 'friendwidgetitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../friendWidgetItem/friendwidgetitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'friendwidgetitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_friendWidgetItem_t {
    QByteArrayData data[15];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_friendWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_friendWidgetItem_t qt_meta_stringdata_friendWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 16), // "friendWidgetItem"
QT_MOC_LITERAL(1, 17, 19), // "SIG_itemSendChatMeg"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 12), // "STRU_CHAT_RQ"
QT_MOC_LITERAL(4, 51, 16), // "SIG_itemSendFile"
QT_MOC_LITERAL(5, 68, 8), // "filesize"
QT_MOC_LITERAL(6, 77, 8), // "fileName"
QT_MOC_LITERAL(7, 86, 5), // "char*"
QT_MOC_LITERAL(8, 92, 4), // "buff"
QT_MOC_LITERAL(9, 97, 4), // "nLen"
QT_MOC_LITERAL(10, 102, 2), // "id"
QT_MOC_LITERAL(11, 105, 23), // "SIG_itemSendFileRequest"
QT_MOC_LITERAL(12, 129, 16), // "CLIENT_FILE_INFO"
QT_MOC_LITERAL(13, 146, 23), // "SIG_itemRecvFileRequest"
QT_MOC_LITERAL(14, 170, 18) // "on_pb_icon_clicked"

    },
    "friendWidgetItem\0SIG_itemSendChatMeg\0"
    "\0STRU_CHAT_RQ\0SIG_itemSendFile\0filesize\0"
    "fileName\0char*\0buff\0nLen\0id\0"
    "SIG_itemSendFileRequest\0CLIENT_FILE_INFO\0"
    "SIG_itemRecvFileRequest\0on_pb_icon_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_friendWidgetItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    5,   42,    2, 0x06 /* Public */,
      11,    1,   53,    2, 0x06 /* Public */,
      13,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 7, QMetaType::Int, QMetaType::QString,    5,    6,    8,    9,   10,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 12,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void friendWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<friendWidgetItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_itemSendChatMeg((*reinterpret_cast< STRU_CHAT_RQ(*)>(_a[1]))); break;
        case 1: _t->SIG_itemSendFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< char*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 2: _t->SIG_itemSendFileRequest((*reinterpret_cast< CLIENT_FILE_INFO(*)>(_a[1]))); break;
        case 3: _t->SIG_itemRecvFileRequest((*reinterpret_cast< CLIENT_FILE_INFO(*)>(_a[1]))); break;
        case 4: _t->on_pb_icon_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (friendWidgetItem::*)(STRU_CHAT_RQ );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&friendWidgetItem::SIG_itemSendChatMeg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (friendWidgetItem::*)(int , QString , char * , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&friendWidgetItem::SIG_itemSendFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (friendWidgetItem::*)(CLIENT_FILE_INFO );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&friendWidgetItem::SIG_itemSendFileRequest)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (friendWidgetItem::*)(CLIENT_FILE_INFO );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&friendWidgetItem::SIG_itemRecvFileRequest)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject friendWidgetItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_friendWidgetItem.data,
    qt_meta_data_friendWidgetItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *friendWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *friendWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_friendWidgetItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int friendWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void friendWidgetItem::SIG_itemSendChatMeg(STRU_CHAT_RQ _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void friendWidgetItem::SIG_itemSendFile(int _t1, QString _t2, char * _t3, int _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void friendWidgetItem::SIG_itemSendFileRequest(CLIENT_FILE_INFO _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void friendWidgetItem::SIG_itemRecvFileRequest(CLIENT_FILE_INFO _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
