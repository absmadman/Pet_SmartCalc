QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    back/credit_back.c \
    back/polishnotation.c \
    back/stack_for_calculations.c \
    back/stack.c \
    credit.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    back/credit_back.h \
    back/stack_for_calculations.h \
    back/stack.h \
    back/polishnotation.h \
    credit.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    mainwindow.ui

TRANSLATIONS += \
    SmartCalc_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    pictures/ac.png \
    pictures/acos.png \
    pictures/as.png \
    pictures/asin.png \
    pictures/atan.png \
    pictures/bg.png \
    pictures/bg_credit.png \
    pictures/bg_old.png \
    pictures/bg_wide.png \
    pictures/calculate.png \
    pictures/close_bracket.png \
    pictures/cos.png \
    pictures/credit.png \
    pictures/degree.png \
    pictures/del.png \
    pictures/divide.png \
    pictures/dot.png \
    pictures/eight.png \
    pictures/equal.png \
    pictures/five.png \
    pictures/four.png \
    pictures/graph.png \
    pictures/graph_light.png \
    pictures/ln.png \
    pictures/log.png \
    pictures/minus.png \
    pictures/mod.png \
    pictures/mul.png \
    pictures/nine.png \
    pictures/one.png \
    pictures/open_bracket.png \
    pictures/plus.png \
    pictures/seven.png \
    pictures/sin.png \
    pictures/sin_pressed.png \
    pictures/six.png \
    pictures/sqrt.png \
    pictures/tan.png \
    pictures/three.png \
    pictures/two.png \
    pictures/x.png \
    pictures/zero.png

RESOURCES += \
    res.qrc
