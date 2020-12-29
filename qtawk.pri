INCLUDEPATH += $$PWD/QtAwk

BASE_OUT_PWD = $$basename(OUT_PWD)
QTAWK_OUT_PWD = $$replace(BASE_OUT_PWD, $$TARGET, QtAwk)

win*:CONFIG(debug, debug|release) {
    LIBS += -L"$$PWD/$$GUMBO_OUT_PWD/debug" -lQtAwk
}
win*:CONFIG(release, debug|release) {
    LIBS += -L"$$PWD/$$GUMBO_OUT_PWD/release" -lQtAwk
}

macx:CONFIG(debug, debug|release) {
    LIBS += -L"$$PWD/$$GUMBO_OUT_PWD" -lQtAwk
}
macx:CONFIG(release, debug|release) {
    LIBS += -L"$$PWD/$$GUMBO_OUT_PWD" -lQtAwk
}
