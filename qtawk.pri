INCLUDEPATH += $$PWD/QtAwk

BASE_OUT_PWD = $$basename(OUT_PWD)
QTAWK_OUT_PWD = $$replace(BASE_OUT_PWD, $$TARGET, QtAwk)

message($$QTAWK_OUT_PWD)

win*:CONFIG(debug, debug|release) {
    LIBS += -L"$$PWD/$$QTAWK_OUT_PWD/debug" -lQtAwk
    message($$LIBS)
}
win*:CONFIG(release, debug|release) {
    LIBS += -L"$$PWD/$$QTAWK_OUT_PWD/release" -lQtAwk
    message($$LIBS)
}

macx:CONFIG(debug, debug|release) {
    LIBS += -L"$$PWD/$$QTAWK_OUT_PWD" -lQtAwk
}
macx:CONFIG(release, debug|release) {
    LIBS += -L"$$PWD/$$QTAWK_OUT_PWD" -lQtAwk
}
