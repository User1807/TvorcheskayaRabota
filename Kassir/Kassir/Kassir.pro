QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clients.cpp \
    endshift.cpp \
    history.cpp \
    main.cpp \
    mainwindow.cpp \
    newclient.cpp \
    newitem.cpp \
    payment.cpp \
    paymentdone.cpp \
    shift.cpp

HEADERS += \
    clients.h \
    endshift.h \
    history.h \
    mainwindow.h \
    newclient.h \
    newitem.h \
    payment.h \
    paymentdone.h \
    shift.h

FORMS += \
    clients.ui \
    endshift.ui \
    history.ui \
    mainwindow.ui \
    newclient.ui \
    newitem.ui \
    payment.ui \
    paymentdone.ui \
    shift.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
