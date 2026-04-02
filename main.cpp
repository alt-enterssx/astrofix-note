#include <QApplication>
#include <QFile>

#include "win/win.h"

int main(int argc, char** argv) {
    QApplication* app = new QApplication(argc, argv);

    QFile* styleFile = new QFile(":/styles/main-theme.qss");
    if (styleFile->open(QFile::Text | QFile::ReadOnly)) {
        QString styleSheet = styleFile->readAll();
        app->setStyleSheet(styleSheet);
    
        styleFile->close();
    }

    Win* win = new Win();
    win->show();

    return app->exec();
}