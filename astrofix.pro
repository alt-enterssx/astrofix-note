QT += widgets core gui

TARGET = AstrofixNote

SOURCES += main.cpp                                                 \
           ./win/win.cpp                                            \
           ./menubar/menubar.cpp                                    \
           ./config/config.cpp                                      \

HEADERS += ./win/win.h                                              \
           ./menubar/menubar.h                                      \
           ./config/config.h                                        \

RESOURCES += ./resources/icons/menubar/icons.qrc                    \
             ./resources/styles/styles.qrc                          \
             ./resources/fonts/fonts.qrc                            \