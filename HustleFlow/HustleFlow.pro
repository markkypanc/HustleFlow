QT       += core gui
QT      = core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/model.cpp \
    View/view.cpp \
    ViewModel/networkmanager.cpp \
    ViewModel/viewmodel.cpp \
    main.cpp \
    contentview.cpp

HEADERS += \
    Model/model.h \
    View/view.h \
    ViewModel/networkmanager.h \
    ViewModel/viewmodel.h \
    constants.h \
    constants.h \
    contentview.h

FORMS += \
    contentview.ui

TRANSLATIONS += \
    HustleFlow_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
