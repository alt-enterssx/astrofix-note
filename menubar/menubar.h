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

#define ABOUT_US_URL "url"
#define TECH_SUPPORT_URl "https://t.me/altenter_code"

class MenuBar: public QWidget 
{
    Q_OBJECT

    public:
        MenuBar(QWidget* parent = nullptr);
        ~MenuBar();

    signals:
        // | Other actions signals
        void hideApplicationActionSignal();
        void openFullScreenActionSignal();


    private slots:
        // | File menu actions methods
        void newFileActionMethod();
        
        void openFileActionMethod();
        void openFolderActionMethod();

        void saveFileActionMethod();
        void autoSaveActionMethod();

        void closeFolderActionMethod();
        void closeApplicationActionMethod();

        // | Other actions method
        void hideApplicationActionMethod();
        void openFullScreenActionMethod();

        // | Edit menu actions methods
        void undoActionMethod();
        void redoActionMethod();

        void copyActionMethod();
        void pasteActionMethod();
        void cutActionMethod();
        void deleteActionMethod();
        
        void selectAllActionMethod();
        void findInFilesMethodAction();

        // | Help menu actions methods
        void aboutUsActionMethod();
        void techSupportActionMethod();

    private:
        // | File menu actions
        QAction* newFileAction;

        QAction* openFileAction;
        QAction* openFolderAction;

        QAction* saveFileAction;
        QAction* autoSaveAction;

        QAction* closeFolderAction;
        QAction* closeApplicationAction;

        // | Edit menu actions
        QAction* undoAction;
        QAction* redoAction;

        QAction* copyAction;
        QAction* pasteAction;
        QAction* cutAction;
        QAction* deleteAction;
        
        QAction* selectAllAction;
        QAction* findInFilesAction;

        // | Help menu actions
        QAction* aboutUsAction;
        QAction* techSupportAction;
};