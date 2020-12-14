TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        glad.c \
        glcontext.cpp \
        glshaderloader.cpp \
        glwindowmanager.cpp \
        main.cpp

unix: copyshaders.commands = $$quote(cp -avr $$PWD/shader/ $${OUT_PWD}/)
win32: copyshaders.commands = $$quote(cmd /c xcopy /Y /S /I $$PWD/shader/ $${OUT_PWD}/)

QMAKE_EXTRA_TARGETS += copyshaders
POST_TARGETDEPS += copyshaders

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lglfw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lglfw3
else:unix: LIBS += -L$$PWD/lib/ -lglfw3

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/release/libglfw3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/libglfw3.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/release/glfw3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/debug/glfw3.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/libglfw3.a

unix|win32: LIBS += -lGL
unix: LIBS += -lpthread -lm -lz -lX11 -lXext -lXfixes -ldl

HEADERS += \
    glcontext.h \
    glheaders.h \
    glshaderloader.h \
    gltypes.h \
    glwindowmanager.h \
    glwindowsettings.h

DISTFILES += \
    shader/fragshader.glsl \
    shader/vertexshader.glsl
