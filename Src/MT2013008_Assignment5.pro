HEADERS       = PLYParser.h \
                GLRenderer.h \
                Window.h \
    Quaternions.h \
    Mesh.h \
    Vertex.h \
    Face.h \
    Edge.h

SOURCES       = main.cpp \
                PLYParser.cpp \
                Window.cpp \
                GLRenderer.cpp \
    Quaternions.cpp \
    Mesh.cpp \
    Vertex.cpp \
    Face.cpp \
    Edge.cpp

QT           += opengl widgets

LIBS += -lassimp -lGL -lGLU -lGLEW -lglut

OTHER_FILES += \
    vshader.glsl \
    fshader.glsl

INSTALLS += ../Build

