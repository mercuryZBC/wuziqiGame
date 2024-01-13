/****************************************************************************
** Meta object code from reading C++ file 'Kernel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Kernel/Kernel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Kernel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Kernel_t {
    QByteArrayData data[30];
    char stringdata0[411];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Kernel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Kernel_t qt_meta_stringdata_Kernel = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Kernel"
QT_MOC_LITERAL(1, 7, 15), // "SIG_loginResult"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "state"
QT_MOC_LITERAL(4, 30, 6), // "iconId"
QT_MOC_LITERAL(5, 37, 8), // "userName"
QT_MOC_LITERAL(6, 46, 7), // "feeling"
QT_MOC_LITERAL(7, 54, 20), // "SIG_FriendInfoComing"
QT_MOC_LITERAL(8, 75, 6), // "userId"
QT_MOC_LITERAL(9, 82, 16), // "SIG_FriendOnline"
QT_MOC_LITERAL(10, 99, 8), // "friendId"
QT_MOC_LITERAL(11, 108, 16), // "SIG_createRoomRs"
QT_MOC_LITERAL(12, 125, 19), // "STRU_CREATE_ROOM_RS"
QT_MOC_LITERAL(13, 145, 19), // "SIG_loadExistRoomRs"
QT_MOC_LITERAL(14, 165, 23), // "STRU_LOAD_EXIST_ROOM_RS"
QT_MOC_LITERAL(15, 189, 18), // "SIG_roomIsBeClosed"
QT_MOC_LITERAL(16, 208, 6), // "roomId"
QT_MOC_LITERAL(17, 215, 14), // "SIG_joinRoomRs"
QT_MOC_LITERAL(18, 230, 17), // "STRU_JOIN_ROOM_RS"
QT_MOC_LITERAL(19, 248, 10), // "joinRoomRs"
QT_MOC_LITERAL(20, 259, 13), // "SIG_gameStart"
QT_MOC_LITERAL(21, 273, 15), // "STRU_GAME_STRAT"
QT_MOC_LITERAL(22, 289, 17), // "SIG_setRemainTime"
QT_MOC_LITERAL(23, 307, 20), // "STRU_SET_REMAIN_TIME"
QT_MOC_LITERAL(24, 328, 17), // "SIG_opponentChess"
QT_MOC_LITERAL(25, 346, 17), // "STRU_PLAYER_CHESS"
QT_MOC_LITERAL(26, 364, 12), // "SIG_gameOver"
QT_MOC_LITERAL(27, 377, 7), // "winSide"
QT_MOC_LITERAL(28, 385, 13), // "dealPlayChess"
QT_MOC_LITERAL(29, 399, 11) // "playerChess"

    },
    "Kernel\0SIG_loginResult\0\0state\0iconId\0"
    "userName\0feeling\0SIG_FriendInfoComing\0"
    "userId\0SIG_FriendOnline\0friendId\0"
    "SIG_createRoomRs\0STRU_CREATE_ROOM_RS\0"
    "SIG_loadExistRoomRs\0STRU_LOAD_EXIST_ROOM_RS\0"
    "SIG_roomIsBeClosed\0roomId\0SIG_joinRoomRs\0"
    "STRU_JOIN_ROOM_RS\0joinRoomRs\0SIG_gameStart\0"
    "STRU_GAME_STRAT\0SIG_setRemainTime\0"
    "STRU_SET_REMAIN_TIME\0SIG_opponentChess\0"
    "STRU_PLAYER_CHESS\0SIG_gameOver\0winSide\0"
    "dealPlayChess\0playerChess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Kernel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   74,    2, 0x06 /* Public */,
       7,    5,   83,    2, 0x06 /* Public */,
       9,    1,   94,    2, 0x06 /* Public */,
      11,    1,   97,    2, 0x06 /* Public */,
      13,    1,  100,    2, 0x06 /* Public */,
      15,    1,  103,    2, 0x06 /* Public */,
      17,    1,  106,    2, 0x06 /* Public */,
      20,    1,  109,    2, 0x06 /* Public */,
      22,    1,  112,    2, 0x06 /* Public */,
      24,    1,  115,    2, 0x06 /* Public */,
      26,    1,  118,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      28,    1,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    3,    8,    5,    4,    6,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21,    2,
    QMetaType::Void, 0x80000000 | 23,    2,
    QMetaType::Void, 0x80000000 | 25,    2,
    QMetaType::Void, QMetaType::Bool,   27,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 25,   29,

       0        // eod
};

void Kernel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Kernel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_loginResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->SIG_FriendInfoComing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 2: _t->SIG_FriendOnline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->SIG_createRoomRs((*reinterpret_cast< STRU_CREATE_ROOM_RS(*)>(_a[1]))); break;
        case 4: _t->SIG_loadExistRoomRs((*reinterpret_cast< STRU_LOAD_EXIST_ROOM_RS(*)>(_a[1]))); break;
        case 5: _t->SIG_roomIsBeClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->SIG_joinRoomRs((*reinterpret_cast< STRU_JOIN_ROOM_RS(*)>(_a[1]))); break;
        case 7: _t->SIG_gameStart((*reinterpret_cast< STRU_GAME_STRAT(*)>(_a[1]))); break;
        case 8: _t->SIG_setRemainTime((*reinterpret_cast< STRU_SET_REMAIN_TIME(*)>(_a[1]))); break;
        case 9: _t->SIG_opponentChess((*reinterpret_cast< STRU_PLAYER_CHESS(*)>(_a[1]))); break;
        case 10: _t->SIG_gameOver((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->dealPlayChess((*reinterpret_cast< STRU_PLAYER_CHESS(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Kernel::*)(int , int , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_loginResult)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(int , QString , QString , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_FriendInfoComing)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_FriendOnline)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(STRU_CREATE_ROOM_RS );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_createRoomRs)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(STRU_LOAD_EXIST_ROOM_RS );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_loadExistRoomRs)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_roomIsBeClosed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(STRU_JOIN_ROOM_RS );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_joinRoomRs)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(STRU_GAME_STRAT );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_gameStart)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(STRU_SET_REMAIN_TIME );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_setRemainTime)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(STRU_PLAYER_CHESS );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_opponentChess)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::SIG_gameOver)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Kernel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Kernel.data,
    qt_meta_data_Kernel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Kernel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kernel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Kernel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Kernel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Kernel::SIG_loginResult(int _t1, int _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Kernel::SIG_FriendInfoComing(int _t1, QString _t2, QString _t3, int _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Kernel::SIG_FriendOnline(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Kernel::SIG_createRoomRs(STRU_CREATE_ROOM_RS _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Kernel::SIG_loadExistRoomRs(STRU_LOAD_EXIST_ROOM_RS _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Kernel::SIG_roomIsBeClosed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Kernel::SIG_joinRoomRs(STRU_JOIN_ROOM_RS _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Kernel::SIG_gameStart(STRU_GAME_STRAT _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Kernel::SIG_setRemainTime(STRU_SET_REMAIN_TIME _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Kernel::SIG_opponentChess(STRU_PLAYER_CHESS _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Kernel::SIG_gameOver(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
