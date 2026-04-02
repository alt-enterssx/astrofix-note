QT += widgets core gui

TARGET = AstrofixNote

SOURCES += main.cpp                                                 \
           ./win/win.cpp                                            \
           ./menubar/menubar.cpp                                    \

HEADERS += ./win/win.h                                              \
           ./menubar/menubar.h                                      \

RESOURCES += ./resources/icons/menubar/icons.qrc                    \
             ./resources/styles/styles.qrc                          \