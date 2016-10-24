TARGET = CommonServer
TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/charsetEncode.cpp \
    src/CPPregex.cpp \
    src/callpy.cpp \
    src/ChtmlTag.cpp \
    src/readFile.cpp

DISTFILES += \
    include/log4cplus/config/stamp-h2 \
    include/log4cplus/stamp-h1 \
    CommonServer.makefile \
    src/CPPcallpy.py

INCLUDEPATH += include  \
    ./../3party/include \
    ./../lib/include/CommonServer   \
    ./../lib/include/ThreadPoolServer

LIBS += -lcurl -ljsoncpp -llog4cplus -lgumbo -lpthread -lzmq  -lboost_regex

unix {
    target.path = ./../lib
    INSTALLS += target
}

HEADERS += \
    include/charsetEncode.h \
    include/common.h \
    include/CPPregex.h \
    include/callpy.h \
    include/readFile.h \
    include/ChtmlTag.h
