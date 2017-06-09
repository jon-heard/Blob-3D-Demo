#-------------------------------------------------
#
# Project created by QtCreator 2017-06-03T03:23:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Metaball3dDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += opengl32.lib

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mesh.cpp \
    editspheredialog.cpp \
    mesh_marchingcubes.cpp \
    mesh_sphere.cpp \
    metaballScene.cpp \
    mesh_metaballs.cpp

HEADERS += \
        mainwindow.h \
    mesh.h \
    editspheredialog.h \
    mesh_marchingcubes.h \
    mesh_sphere.h \
    metaballScene.h \
    mesh_metaballs.h

FORMS += \
        mainwindow.ui \
    editspheredialog.ui

DISTFILES += \
    backlog.txt

RESOURCES += \
    resources.qrc