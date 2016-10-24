TARGET = MainServer
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    client/client.cpp \
    src/crawlstruct.cpp \
    src/main.cpp \
    src/testurls.cpp \
    tools/loadfile.cpp

DISTFILES += \
    include/log4cplus/config/stamp-h2 \
    include/log4cplus/stamp-h1 \
    MainServer \
    build.sh \
    checkapp.sh \
    checkbusline.sh \
    configure \
    a.txt \
    url.conf \
    url.txt \
    image.log \
    README.md \
    makefile

INCLUDEPATH += include  \
    ./../3party/include \
    ./../lib/include/CommonServer   \
    ./../lib/include/ThreadPoolServer   \
    ./../lib/include/CrawlServer    \
    ./../lib/include/LogServer  \
    ./../lib/include/DBServer   \
    ./../lib/include/GumboServer

LIBS += -lcurl -ljsoncpp -llog4cplus -lpthread -lgumbo -lzmq -L./../lib/*.so

HEADERS += \
    include/crawlstruct.h \
    include/testurls.h
