QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    gameobject.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    BasicIO.h \
    gameobject.h \
    mainwidget.h \
    geometryengine.h \
    transform.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
	mesh.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target


