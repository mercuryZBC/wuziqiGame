/****************************************************************************
** Meta object code from reading C++ file 'gamedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../gamedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameDialog_t {
    QByteArrayData data[18];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameDialog_t qt_meta_stringdata_GameDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameDialog"
QT_MOC_LITERAL(1, 11, 24), // "SIG_exitOnlineGameDialog"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 6), // "roomId"
QT_MOC_LITERAL(4, 44, 13), // "SIG_readyGame"
QT_MOC_LITERAL(5, 58, 15), // "SIG_playerChess"
QT_MOC_LITERAL(6, 74, 17), // "STRU_PLAYER_CHESS"
QT_MOC_LITERAL(7, 92, 13), // "setRemainTime"
QT_MOC_LITERAL(8, 106, 19), // "setOnlineRemainTime"
QT_MOC_LITERAL(9, 126, 20), // "STRU_SET_REMAIN_TIME"
QT_MOC_LITERAL(10, 147, 23), // "on_pb_startGame_clicked"
QT_MOC_LITERAL(11, 171, 15), // "onlineGameStart"
QT_MOC_LITERAL(12, 187, 15), // "STRU_GAME_STRAT"
QT_MOC_LITERAL(13, 203, 13), // "gameStartPack"
QT_MOC_LITERAL(14, 217, 19), // "opponentChessComing"
QT_MOC_LITERAL(15, 237, 11), // "palyerChess"
QT_MOC_LITERAL(16, 249, 14), // "gameOverComing"
QT_MOC_LITERAL(17, 264, 7) // "winSide"

    },
    "GameDialog\0SIG_exitOnlineGameDialog\0"
    "\0roomId\0SIG_readyGame\0SIG_playerChess\0"
    "STRU_PLAYER_CHESS\0setRemainTime\0"
    "setOnlineRemainTime\0STRU_SET_REMAIN_TIME\0"
    "on_pb_startGame_clicked\0onlineGameStart\0"
    "STRU_GAME_STRAT\0gameStartPack\0"
    "opponentChessComing\0palyerChess\0"
    "gameOverComing\0winSide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   68,    2, 0x0a /* Public */,
       8,    1,   69,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    1,   73,    2, 0x0a /* Public */,
      14,    1,   76,    2, 0x0a /* Public */,
      16,    1,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 6,   15,
    QMetaType::Void, QMetaType::Bool,   17,

       0        // eod
};

void GameDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_exitOnlineGameDialog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SIG_readyGame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SIG_playerChess((*reinterpret_cast< STRU_PLAYER_CHESS(*)>(_a[1]))); break;
        case 3: _t->setRemainTime(); break;
        case 4: _t->setOnlineRemainTime((*reinterpret_cast< STRU_SET_REMAIN_TIME(*)>(_a[1]))); break;
        case 5: _t->on_pb_startGame_clicked(); break;
        case 6: _t->onlineGameStart((*reinterpret_cast< STRU_GAME_STRAT(*)>(_a[1]))); break;
        case 7: _t->opponentChessComing((*reinterpret_cast< STRU_PLAYER_CHESS(*)>(_a[1]))); break;
        case 8: _t->gameOverComing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameDialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDialog::SIG_exitOnlineGameDialog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameDialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDialog::SIG_readyGame)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameDialog::*)(STRU_PLAYER_CHESS );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameDialog::SIG_playerChess)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_GameDialog.data,
    qt_meta_data_GameDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int GameDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GameDialog::SIG_exitOnlineGameDialog(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameDialog::SIG_readyGame(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameDialog::SIG_playerChess(STRU_PLAYER_CHESS _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
