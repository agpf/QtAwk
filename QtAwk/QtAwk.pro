QT -= gui

TEMPLATE = lib
DEFINES += QTAWK_LIBRARY

CONFIG += c++11 staticlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../awk/b.cpp \
    ../awk/lex.cpp \
    ../awk/lib.cpp \
    ../awk/libmain.cpp \
    ../awk/parse.cpp \
    ../awk/run.cpp \
    ../awk/tran.cpp \
    ../awk/ytab.cpp \
    qtawk.cpp

HEADERS += \
    ../awk/awk.h \
    ../awk/proto.h \
    ../awk/ytab.h \
    ../include/awkerr.h \
    ../include/awklib.h \
    qtawk.h

INCLUDEPATH += $$PWD/awk/

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
win32 {
    target.path = $$PWD/../lib
    message($$target.path)
}
!isEmpty(target.path): INSTALLS += target
