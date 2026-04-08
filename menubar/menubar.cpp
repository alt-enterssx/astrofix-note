#include "menubar.h"

// | Constructor
MenuBar::MenuBar(Config* config, QWidget* parent): QWidget(parent), config(config) {

    // | Config init
    if(!config) {
        qWarning() << "Error in init config";
    }

    // | Base settings of menu bar
    this->setObjectName("menuBar");

    this->setFixedHeight(35);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    mainLayout->setContentsMargins(15, 0, 15, 0);

    this->setLayout(mainLayout);

    // | Menus layout
    QHBoxLayout* menusLayout = new QHBoxLayout();
    {
        mainLayout->addLayout(menusLayout, 1);

        menusLayout->setContentsMargins(0, 0, 0, 0);
        menusLayout->setSpacing(8);

        // | File Menu
        QToolButton* fileMenuBtn = new QToolButton();
        {
            menusLayout->addWidget(fileMenuBtn);

            fileMenuBtn->setFixedHeight(26);
            fileMenuBtn->setText("File");
            fileMenuBtn->setPopupMode(QToolButton::InstantPopup);

            QMenu* fileMenu = new QMenu(fileMenuBtn);
            fileMenuBtn->setMenu(fileMenu);

            this->openFileAction = fileMenu->addAction("Open File", QKeySequence("Ctrl+O"), this, &MenuBar::openFileActionMethod);
            this->openFolderAction = fileMenu->addAction("Open Folder", QKeySequence("Ctrl+Shift+O"), this, &MenuBar::openFolderActionMethod);
        
            fileMenu->addSeparator();
        
            this->saveFileAction = fileMenu->addAction("Save File", QKeySequence("Ctrl+S"), this, &MenuBar::saveFileActionMethod);
            
            this->autoSaveAction = fileMenu->addAction("AutoSave", this, &MenuBar::autoSaveActionMethod);
            this->autoSaveAction->setCheckable(true);

            fileMenu->addSeparator();

            this->closeApplicationAction = fileMenu->addAction("Quit", QKeySequence("Ctrl+Q"), this, &MenuBar::closeApplicationActionMethod);
        }

        // | Edit Menu
        QToolButton* editMenuBtn = new QToolButton();
        {
            menusLayout->addWidget(editMenuBtn);

            editMenuBtn->setFixedHeight(26);
            editMenuBtn->setText("Edit");
            editMenuBtn->setPopupMode(QToolButton::InstantPopup);

            QMenu* editMenu = new QMenu(editMenuBtn);
            editMenuBtn->setMenu(editMenu);

            this->undoAction = editMenu->addAction("Undo", QKeySequence("Ctrl+Z"), this, &MenuBar::undoActionMethod);
            this->redoAction = editMenu->addAction("Redo", QKeySequence("Ctrl+Y"), this, &MenuBar::redoActionMethod);

            editMenu->addSeparator();

            this->copyAction = editMenu->addAction("Copy", QKeySequence("Ctrl+C"), this, &MenuBar::copyActionMethod);
            this->pasteAction = editMenu->addAction("Paste", QKeySequence("Ctrl+P"), this, &MenuBar::pasteActionMethod);
            this->cutAction = editMenu->addAction("Cut", QKeySequence("Ctrl+x"), this, &MenuBar::cutActionMethod);
            this->selectAllAction = editMenu->addAction("Select All", QKeySequence("Ctrl+A"), this, &MenuBar::selectAllActionMethod);
        }

        // | Help Menu
        QToolButton* helpMenuBtn = new QToolButton();
        {
            menusLayout->addWidget(helpMenuBtn);

            helpMenuBtn->setFixedHeight(26);
            helpMenuBtn->setText("Help");
            helpMenuBtn->setPopupMode(QToolButton::InstantPopup);

            QMenu* helpMenu = new QMenu(helpMenuBtn);
            helpMenuBtn->setMenu(helpMenu);

            this->aboutUsAction = helpMenu->addAction("About Us", this, &MenuBar::aboutUsActionMethod);
            this->techSupportAction = helpMenu->addAction("Technical Support", this, &MenuBar::techSupportActionMethod);
        }

    }

    mainLayout->addStretch();

    // | Buttons layout
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    {
        mainLayout->addLayout(buttonsLayout, 1);

        buttonsLayout->setContentsMargins(0, 0, 0, 0);
        buttonsLayout->setSpacing(15);

        // | View buttons layout
        QHBoxLayout* viewButtonsLayout = new QHBoxLayout();
        {
            buttonsLayout->addLayout(viewButtonsLayout);

            viewButtonsLayout->setContentsMargins(0, 0, 0, 0);
            viewButtonsLayout->setSpacing(8);

            this->showLeftSideBarBtn = new QPushButton();
            this->showLeftSideBarBtn->setIcon(QIcon(":/menubar/icons/show_left_side_bar_enable.svg"));
            this->showLeftSideBarBtn->setIconSize(QSize(12, 12));

            this->showLeftSideBarBtn->setFixedSize(26, 26);
            
            connect(this->showLeftSideBarBtn, &QPushButton::clicked, this, &MenuBar::showLeftSideBarMethod);

            viewButtonsLayout->addWidget(this->showLeftSideBarBtn);
        }

        // | Window buttons layout
        QHBoxLayout* windowButtonsLayout = new QHBoxLayout();
        {
            buttonsLayout->addLayout(windowButtonsLayout);

            windowButtonsLayout->setContentsMargins(0, 0, 0, 0);
            windowButtonsLayout->setSpacing(8);

            QPushButton* hideBtn = new QPushButton();
            hideBtn->setShortcut(QKeySequence("Ctrl+Shift+H"));

            hideBtn->setIcon(QIcon(":/menubar/icons/hide.svg"));
            hideBtn->setIconSize(QSize(10, 10));
            
            hideBtn->setFixedSize(26, 26);

            
            connect(hideBtn, &QPushButton::clicked, this, &MenuBar::hideApplicationActionMethod);

            windowButtonsLayout->addWidget(hideBtn);

            this->showFullScreenBtn = new QPushButton();
            this->showFullScreenBtn->setShortcut(QKeySequence("Ctrl+F"));

            this->showFullScreenBtn->setIcon(QIcon(":/menubar/icons/fullscreen.svg"));
            this->showFullScreenBtn->setIconSize(QSize(10, 10));

            this->showFullScreenBtn->setFixedSize(26, 26);

            connect(this->showFullScreenBtn, &QPushButton::clicked, this, &MenuBar::openFullScreenActionMethod);

            windowButtonsLayout->addWidget(this->showFullScreenBtn);

            QPushButton* exitBtn = new QPushButton();
            exitBtn->setIcon(QIcon(":/menubar/icons/exit.svg"));
            exitBtn->setIconSize(QSize(10, 10));

            exitBtn->setFixedSize(26, 26);

            connect(exitBtn, &QPushButton::clicked, this, &MenuBar::closeApplicationActionMethod);

            windowButtonsLayout->addWidget(exitBtn);
        }

        // | Config set
        this->autoSaveAction->setChecked(this->config->getAutoSaveSt());

    }

}

// | File menu actions methods
void MenuBar::openFileActionMethod() {
    QString filePath = QFileDialog::getOpenFileName(
        this, QString("Select File"),
        QDir::homePath()
    );

    if (filePath.isEmpty()) { return; }

    Config::Path path = Config::Path();
    path.path = filePath.toStdString();
    path.type = Config::Path::PathType::FILE;

    this->config->setCurrentPath(&path);
    emit openFileActionSignal(filePath);
}
void MenuBar::openFolderActionMethod() {
    QString folderPath = QFileDialog::getExistingDirectory(
        this, QString("Select Folder"),
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (folderPath.isEmpty()) { return; }

    Config::Path path = Config::Path(Config::Path::PathType::FOLDER, folderPath.toStdString());
    this->config->setCurrentPath(&path);

    emit openFolderActionSignal(folderPath);
}

void MenuBar::saveFileActionMethod() {
    emit saveCurrentFileActionSignal();
}
void MenuBar::autoSaveActionMethod() {
    this->config->setAutoSaveSt(this->autoSaveAction->isChecked());
}

void MenuBar::closeApplicationActionMethod() {
    QApplication::quit();
}


// | Window actions method
void MenuBar::hideApplicationActionMethod() {
    emit MenuBar::hideApplicationActionSignal();
}
void MenuBar::openFullScreenActionMethod() {
    emit MenuBar::openFullScreenActionSignal(this->showFullScreenBtn);
}


// | Edit menu actions methods
void MenuBar::undoActionMethod() {
    emit undoActionSignal();
}
void MenuBar::redoActionMethod() {
    emit redoActionSignal();
}

void MenuBar::copyActionMethod() {
    emit copyActionSignal();
}
void MenuBar::pasteActionMethod() {
    emit pasteActionSignal();
}
void MenuBar::cutActionMethod() {
    emit cutActionSignal();
}
void MenuBar::selectAllActionMethod() {
    emit selectAllActionSignal();
}

// | Help menu actions methods
void MenuBar::aboutUsActionMethod() {
    QUrl url = QUrl(ABOUT_US_URL);
    QDesktopServices::openUrl(url);
}
void MenuBar::techSupportActionMethod() {
    QUrl url = QUrl(TECH_SUPPORT_URl);
    QDesktopServices::openUrl(url);
}

// | View actions
void MenuBar::showLeftSideBarMethod() {
    emit showLeftSideBarSignal(this->showLeftSideBarBtn);
}

// | Destructor
MenuBar::~MenuBar() {}