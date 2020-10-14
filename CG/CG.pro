QT += opengl

TARGET = CG
TEMPLATE = app
SOURCES +=  \
            main.cpp
HEADERS +=
RESOURCES +=

win32 {
    INCLUDEPATH +=
    LIBS += \
        -lopengl32 \
        -lglu32
}

unix {
    INCLUDEPATH += /usr/include
    LIBS += \
        -lGL \
        -lGLU
}


DISTFILES += \
    glut32.dll

LIBS+=-lglut32


