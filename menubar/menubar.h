#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QApplication>
#include <QUrl>
#include <QDesktopServices>
#include <QFileDialog>
#include <QDir>

#include "../config/config.h"

#define ABOUT_US_URL "https://github.com/alt-enterssx"
#define TECH_SUPPORT_URl "https://t.me/altenter_code"

class MenuBar: public QWidget 
{
    Q_OBJECT

    public:
        MenuBar(Config* config, QWidget* parent = nullptr);
        ~MenuBar();

    signals:
        // | File menu actions signals
        void openFileActionSignal(QString path);
        void openFolderActionSignal(QString path);
        void saveCurrentFileActionSignal();

        // | Other actions signals
        void hideApplicationActionSignal();
        void openFullScreenActionSignal(QPushButton* fullScreenBtn);

        // | Code editor action signals
        void undoActionSignal();
        void redoActionSignal();
        
        void copyActionSignal();
        void pasteActionSignal();
        void cutActionSignal();
        void selectAllActionSignal();

        // | View signals
        void showLeftSideBarSignal(QPushButton* leftSideBarBtn);

    private slots:

        // | File menu actions methods
        void openFileActionMethod();
        void openFolderActionMethod();

        void saveFileActionMethod();
        void autoSaveActionMethod();

        void closeApplicationActionMethod();

        // Window actions method
        void hideApplicationActionMethod();
        void openFullScreenActionMethod();

        // | Edit menu actions methods
        void undoActionMethod();
        void redoActionMethod();

        void copyActionMethod();
        void pasteActionMethod();
        void cutActionMethod();
        void selectAllActionMethod();

        // | Help menu actions methods
        void aboutUsActionMethod();
        void techSupportActionMethod();

        // | View actions
        void showLeftSideBarMethod();

    private:
        // | Config
        Config* config;

        // | File menu actions
        QAction* openFileAction;
        QAction* openFolderAction;

        QAction* saveFileAction;
        QAction* autoSaveAction;

        QAction* closeApplicationAction;

        // | Edit menu actions
        QAction* undoAction;
        QAction* redoAction;

        QAction* copyAction;
        QAction* pasteAction;
        QAction* cutAction;
        QAction* selectAllAction;

        // | Help menu actions
        QAction* aboutUsAction;
        QAction* techSupportAction;

        // | Ui states widget
        QPushButton* showFullScreenBtn;
        QPushButton* showLeftSideBarBtn;
};