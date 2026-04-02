QT += widgets core gui

TARGET = AstrofixNote

SOURCES += main.cpp                                                 \
           ./win/win.cpp                                            \
           ./menubar/menubar.cpp                                    \
           ./config/config.cpp                                      \
           ./code_block/code_block.cpp                              \
           ./code_block/code_editor/code_editor.cpp                 \

HEADERS += ./win/win.h                                              \
           ./menubar/menubar.h                                      \
           ./config/config.h                                        \
           ./code_block/code_block.h                                \
           ./code_block/code_editor/code_editor.h                   \

RESOURCES += ./resources/icons/menubar/icons.qrc                    \
             ./resources/styles/styles.qrc                          \
             ./resources/fonts/fonts.qrc                            \