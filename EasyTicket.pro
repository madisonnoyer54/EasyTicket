QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    administrateur.cpp \
    administrateurwidget.cpp \
    categorie.cpp \
    clientwidget.cpp \
    connexionwidget.cpp \
    dialogassignerticket.cpp \
    dialognouveauticket.cpp \
    dialogticket.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    objetobserve.cpp \
    technicienwidget.cpp \
    client.cpp \
    gestionnairedialogue.cpp \
    technicien.cpp \
    ticket.cpp \
    utilisateur.cpp

HEADERS += \
    administrateur.h \
    administrateurwidget.h \
    clientwidget.h \
    connexionwidget.h \
    dialogassignerticket.h \
    dialognouveauticket.h \
    dialogticket.h \
    mainwindow.h \
    message.h \
    objetobserve.h \
    observeur.h \
    technicienwidget.h \
    categorie.h \
    client.h \
    gestionnairedialogue.h \
    technicien.h \
    ticket.h \
    utilisateur.h

FORMS += \
    administrateurwidget.ui \
    clientwidget.ui \
    connexionwidget.ui \
    dialogassignerticket.ui \
    dialognouveauticket.ui \
    dialogticket.ui \
    mainwindow.ui \
    technicienwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    database.qrc \
    icon.qrc

ICON = icon.ico
