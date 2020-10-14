QT += opengl widgets

TARGET = V2
TEMPLATE = app
SOURCES +=  \
            main.cpp \
            glwidget.cpp
HEADERS +=  \
            glwidget.h
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

