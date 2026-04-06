#pragma once

#include <QPlainTextEdit>
#include <QFile>
#include <QKeyEvent>
#include <QTextCursor>
#include <QTextBlock>
#include <QTimer>
#include <QClipboard>
#include <QGuiApplication>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QFileInfo>
#include <cstdlib>

#include "../../config/config.h"

class CodeEditor: public QPlainTextEdit 
{
    Q_OBJECT

    public:
        CodeEditor(Config* config, QWidget* parent = nullptr);
        ~CodeEditor();
 
    protected:
        // | KeyPress filters
        void keyPressEvent(QKeyEvent* event) override;
        void charsFilter(QTextCursor* cursor, QChar sym, QKeyEvent* event);
        void modifiersFilter(QTextCursor* cursor, QKeyEvent* event);

        // | Context menu event
        void contextMenuEvent(QContextMenuEvent* event);

    public slots: 
        // | File works
        void saveCurrentFileMethod();
        void openFileMethod(QString path);

        // | Slots for signals
        void onTextChanged();

        // | Slots for timers
        void autoSaveMethod();

        // | Modifiers methods
        void copyHandle();
        void pasteHandle();
        void cutHandle();
        void selectAllHandle();

    private:
        // | Config
        Config* config;

        // | Other
        QFile* currentFile;

        // | Timers
        QTimer* autoSaveTimer;

        // | Visual methods
        void highlightCurrentLine();
};