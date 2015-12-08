#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T18:14:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Synthese

TEMPLATE = app

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp


SOURCES += main.cpp \
    terrainimage.cpp \
    terrain.cpp \
    mathutils.cpp \
    smoothnoise.cpp \
    ray.cpp \
    camera.cpp \
    vector2d.cpp \
    vector3d.cpp \
    terrainnoise.cpp \
    terrainnoisesmultiples.cpp \
    mesh.cpp \
    meshbuilder.cpp \
    terraintest.cpp \
    matrix3.cpp

HEADERS += \
    terrain.h \
    terrainimage.h \
    mathutils.h \
    smoothnoise.h \
    ray.h \
    camera.h \
    vector2d.h \
    vector3d.h \
    terrainnoise.h \
    terrainnoisesmultiples.h \
    mesh.h \
    meshbuilder.h \
    terraintest.h \
    matrix3.h
