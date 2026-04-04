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
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    centralWidget->setLayout(mainLayout);

    // | MenuBar widget
    this->menuBar = new MenuBar(config, this);
    this->setMenuWidget(menuBar);

    // | Central layout
    QHBoxLayout* centralLayout = new QHBoxLayout();
    centralLayout->setContentsMargins(0, 0, 0, 0);
    centralLayout->setSpacing(0);

    mainLayout->addLayout(centralLayout);

    // | CodeBlock widget
    this->codeBlock = new CodeBlock(config);
    centralLayout->addWidget(this->codeBlock);

    // | Connects

    // | Connects of MenuBar
    connect(this->menuBar, &MenuBar::saveCurrentFileActionSignal, this->codeBlock, &CodeBlock::saveCurrentFileWrapper);

    connect(this->menuBar, &MenuBar::hideApplicationActionSignal, this, &Win::hideApplication);
    connect(this->menuBar, &MenuBar::openFullScreenActionSignal, this, &Win::openFullScreen);
}

// | MenuBar slots
void Win::openFullScreen(QPushButton* fullScreenBtn) {
    if (this->isFullScreen()) { 
        this->showNormal(); 
        fullScreenBtn->setIcon(QIcon(":/menubar/icons/fullscreen.svg"));
    } else { 
        this->showFullScreen(); 
        fullScreenBtn->setIcon(QIcon(":/menubar/icons/normal.svg"));
    }
}

void Win::hideApplication() {
    this->hide();
}

// | Destructor
Win::~Win() {}