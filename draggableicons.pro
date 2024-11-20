QT += widgets

HEADERS     = dragwidget.h \
    coordinatesystem.h \
    joint.h \
    jointTypes.h \
    logWidget.h \
    mainwindow.h \
    structureWidget.h
RESOURCES   = draggableicons.qrc \
    draggableicons.qrc
SOURCES     = dragwidget.cpp \
              coordinatesystem.cpp \
              joint.cpp \
              logWidget.cpp \
              main.cpp \
              mainwindow.cpp \
              structureWidget.cpp
wasm {
   QMAKE_LFLAGS += -sASYNCIFY -Os
}
# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/draganddrop/draggableicons
INSTALLS += target
