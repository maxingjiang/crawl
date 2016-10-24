TARGET = CrawlServer
TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/Accept.cpp \
    src/AcceptEncoding.cpp \
    src/CCookie.cpp \
    src/CCookieManager.cpp \
    src/CCrawl.cpp \
    src/CCrawlManager.cpp \
    src/CHttpRequest.cpp \
    src/CProxyManager.cpp \
    src/CRequestHeaders.cpp \
    src/CRequestUrl.cpp \
    src/CResponseBody.cpp \
    src/CResponseHeaders.cpp \
    src/insertRequestHeadersData.cpp \
    src/Proxy.cpp \
    src/Referer.cpp \
    src/RequestCookie.cpp \
    src/RequestPostdata.cpp \
    src/ResponseCookie.cpp \
    src/split.cpp \
    src/stringList.cpp \
    src/UserAgent.cpp \
    src/AcceptLanguage.cpp \
    src/postLogin.cpp \
    src/singleCrawl.cpp

DISTFILES += \
    include/log4cplus/config/stamp-h2 \
    include/log4cplus/stamp-h1 \
    conf/requestHeadersConf/default.requestheaders \
    conf/requestHeadersConf/douban.requestheaders \
    conf/requestHeadersConf/jd.requestheaders \
    conf/requestHeadersConf/tianya.requestheaders \
    conf/requestHeadersConf/weibo.requestheaders \
    conf/requestHeadersConf/zhihu.requestheaders \
    conf/proxy.conf \
    CrawlServer.makefile

INCLUDEPATH += include \
    /usr/include/mysql  \
    ./../lib/include/DBServer   \
    ./../lib/include/LogServer  \
    ./../lib/include/ThreadPoolServer   \
    ./../lib/include/CommonServer   \
    ./../3party/include \

LIBS += -lcurl -ljsoncpp -llog4cplus -lgumbo -lpthread -lzmq -L./../lib/*.so

unix {
    target.path = ./../lib
    INSTALLS += target
}

HEADERS += \
    include/Accept.h \
    include/AcceptEncoding.h \
    include/CCookie.h \
    include/CCookieManager.h \
    include/CCrawl.h \
    include/CCrawlManager.h \
    include/CHttpRequest.h \
    include/common.h \
    include/CProxyManager.h \
    include/CRequestHeaders.h \
    include/CRequestUrl.h \
    include/CResponseBody.h \
    include/CResponseHeaders.h \
    include/insertRequestHeadersData.h \
    include/Proxy.h \
    include/Referer.h \
    include/RequestCookie.h \
    include/RequestPostdata.h \
    include/ResponseCookie.h \
    include/split.h \
    include/stringList.h \
    include/UserAgent.h \
    ../DBServer/include \
    include/AcceptLanguage.h \
    include/postLogin.h \
    include/singleCrawl.h
