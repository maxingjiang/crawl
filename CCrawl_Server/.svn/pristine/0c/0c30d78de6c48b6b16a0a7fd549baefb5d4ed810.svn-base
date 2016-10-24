TARGET = SocketServer
TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/runSocket.cpp

DISTFILES += \
    include/log4cplus/config/stamp-h2 \
    include/log4cplus/stamp-h1 \
    SocketServer.makefile

INCLUDEPATH += include  \
    ./../3party/include \
    ./../lib/include/CommonServer   \
    ./../lib/include/ThreadPoolServer

LIBS += -lcurl -ljsoncpp -llog4cplus -lgumbo -lpthread -lzmq

unix {
    target.path = ./../lib
    INSTALLS += target
}

HEADERS += \
    include/SockerServer.h
