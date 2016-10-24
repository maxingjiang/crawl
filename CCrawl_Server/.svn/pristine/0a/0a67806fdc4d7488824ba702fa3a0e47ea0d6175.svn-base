TARGET = ThreadPoolServer
TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/threadpool.cpp

DISTFILES += \
    include/log4cplus/config/stamp-h2 \
    include/log4cplus/stamp-h1 \
    ThreadPoolServer.makefile

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
    include/threadpool.h
