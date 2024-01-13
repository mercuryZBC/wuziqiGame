QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtWuziqi
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    INet/TcpClientNet.cpp \
    Kernel/Kernel.cpp \
    NetMediator/INetMediator.cpp \
    NetMediator/TcpClientNetMediator.cpp \
    chessboardwidget.cpp \
    friendWidgetItem/friendwidgetitem.cpp \
    gamedialog.cpp \
    gamelobbydialog.cpp \
    gameroomwidgetitem.cpp \
        mainwindow.cpp \
    GameModel.cpp \
    playerinfo.cpp \
    startdialog.cpp

HEADERS  += mainwindow.h \
    Config/ClientConfig.h \
    Config/GameConfig.h \
    Config/config.h \
    GameModel.h \
    INet/INet.h \
    INet/TcpClientNet.h \
    Kernel/Kernel.h \
    NetMediator/INetMediator.h \
    NetMediator/TcpClientNetMediator.h \
    chessboardwidget.h \
    friendWidgetItem/friendwidgetitem.h \
    gamedialog.h \
    gamelobbydialog.h \
    gameroomwidgetitem.h \
    playerinfo.h \
    startdialog.h

RESOURCES += \
    resource.qrc

LIBS += \
    -lws2_32

FORMS += \
    chessboardwidget.ui \
    friendWidgetItem/friendwidgetitem.ui \
    gamedialog.ui \
    gamelobbydialog.ui \
    gameroomwidgetitem.ui \
    mainwindow.ui \
    playerinfo.ui \
    startdialog.ui
