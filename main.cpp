#include <QApplication>
#include "win/win.h"

int main(int argc, char** argv) {
    QApplication* app = new QApplication(argc, argv);

    Win* win = new Win();
    win->show();

    return app->exec();
}