QT       += core gui
TARGET = CWebPageServer
TEMPLATE = app
CONFIG += console c++11
CONFIG += app_bundle
CONFIG += qt

SOURCES += main.cpp \
    src/CAfterProcess.cpp \
    src/CArticle.cpp \
    src/CBaseItem.cpp \
    src/CCollector.cpp \
    src/CCollectorManager.cpp \
    src/CCopyrightProtection.cpp \
    src/CInterpreter.cpp \
    src/CObtainCode.cpp \
    src/CPublishRule.cpp \
    src/CRule.cpp \
    src/CRuleItem.cpp \
    src/CRuleManager.cpp \
    src/CRuleMatchInfo.cpp \
    src/CRuleType.cpp \
    src/CWebPage.cpp \
    src/CWebPageMgr.cpp \
    src/CThreadManager.cpp \
    src/CTaskManager.cpp \
    src/CTask.cpp   \
    src/CTasks.cpp \
    src/CJob.cpp   \
    src/CJobMgr.cpp   \
    src/CMission.cpp   \
    src/CMissionMgr.cpp   \
    src/CMissions.cpp   \
    src/CMissionMap.cpp

DISTFILES += \
    include/log4cplus/config/stamp-h2 \
    include/log4cplus/stamp-h1 \
    core \
    CWebPageServer \
    CWebPageServer.makefile \
    makefile

INCLUDEPATH += ./include \
    /usr/include/mysql  \
    ./../3party/include \
    ./../lib/include/CommonServer   \
    ./../lib/include/ThreadPoolServer   \
    ./../lib/include/LogServer  \
    ./../lib/include/CrawlServer    \
    ./../lib/include/DBServer   \
    ./../lib/include/CWebPageServer \
    ./../lib/include/GumboServer

LIBS += -lcurl -ljsoncpp -llog4cplus -lgumbo -lpthread -lzmq -lmysqlclient -lpthread -L./../lib/*.so


HEADERS += \
    include/CAfterProcess.h \
    include/CArticle.h \
    include/CBaseItem.h \
    include/CCollector.h \
    include/CCollectorManager.h \
    include/CCopyrightProtection.h \
    include/CInterpreter.h \
    include/CObtainCode.h \
    include/CPublishRule.h \
    include/CRule.h \
    include/CRuleItem.h \
    include/CRuleManager.h \
    include/CRuleMatchInfo.h \
    include/CRuleType.h \
    include/CWebPage.h \
    include/CWebPageMgr.h \
    include/include.h \
    include/CThreadManager.h \
    include/CTaskManager.h \
    include/CTask.h   \
    include/CTasks.h \
    include/CJob.h   \
    include/CJobMgr.h   \
    include/CMission.h   \
    include/CMissionMgr.h   \
    include/CMissions.h   \
    include/CMissionMap.h
