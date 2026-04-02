#include "win.h"

// | Contructor
Win::Win(QWidget* parent): QMainWindow(parent) {
    // | Settings initialization
    QSettings* settings = new QSettings("korean", "astrofix-note");
    Config* config = new Config(settings);

    // | Auto reisze and central window
    QScreen* screen = QGuiApplication::primaryScreen();
    if (screen) {
        int screenWidth = screen->geometry().width();
        int screenHeight = screen->geometry().height();
    
        int winWidth = screenWidth * 7 / 10;
        int winHeight = screenHeight * 7 / 10;
    
        this->setGeometry((screenWidth - winWidth) / 2, (screenHeight - winHeight) / 2, winWidth, winHeight);
    }

    this->setWindowFlag(Qt::FramelessWindowHint);

    // | Main layout and centralWidget
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    // | MenuBar Widget
    this->menuBar = new MenuBar(config, this);
    this->setMenuWidget(menuBar);

    // | Connects

    // | Connects of MenuBar
    connect(this->menuBar, &MenuBar::hideApplicationActionSignal, this, &Win::hideApplication);
    connect(this->menuBar, &MenuBar::openFullScreenActionSignal, this, &Win::openFullScreen);

} 

// | MenuBar slots
void Win::openFullScreen() {
    if (this->isFullScreen()) { this->showNormal(); }
    else { this->showFullScreen(); }
}

void Win::hideApplication() {
    this->hide();
}

// | Destructor
Win::~Win() {}