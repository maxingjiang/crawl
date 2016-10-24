TARGET = DBServer
TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/CDBServer.cpp \
    src/MysqlService.cpp

DISTFILES += \
    include/log4cplus/config/stamp-h2 \
    include/log4cplus/stamp-h1 \
    buildmysql.sh \
    DBServer.makefile \
    crawldb.sql

INCLUDEPATH += /usr/include/mysql \
    include \
    ../CommonServer/include

LIBS += -lcurl -ljsoncpp -llog4cplus -lgumbo -lpthread -lzmq -lmysqlclient -lpthread


unix {
    target.path = ./../lib
    INSTALLS += target
}

HEADERS += \
    include/CDBServer.h \
    include/MysqlService.h  \

