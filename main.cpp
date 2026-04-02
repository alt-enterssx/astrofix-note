#include <QApplication>
#include <QFile>
#include <QCoreApplication>
#include <QFontDatabase>

#include "win/win.h"

int main(int argc, char** argv) {
    QApplication* app = new QApplication(argc, argv);

    // | Settings 
    QCoreApplication::setOrganizationDomain("korean.io");

    // | Fonts
    int jetBrainsFont = QFontDatabase::addApplicationFont(":/fonts/JetBrains_Mono.ttf");

    // | Set styleSheet
    QFile* styleFile = new QFile(":/styles/main-theme.qss");
    if (styleFile->open(QFile::Text | QFile::ReadOnly)) {
        QString styleSheet = styleFile->readAll();
        app->setStyleSheet(styleSheet);
    
        styleFile->close();
    }

    // | Win initialization
    Win* win = new Win();
    win->show();

    return app->exec();
}