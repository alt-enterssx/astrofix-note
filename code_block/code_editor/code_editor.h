#pragma once

#include <QPlainTextEdit>
#include <QFile>
#include <QKeyEvent>
#include <QTextCursor>
#include <QTextBlock>
#include <QTimer>
#include <cstdlib>
#include <QClipboard>
#include <QGuiApplication>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>

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
        Config* config;

        // | Timers
        QTimer* autoSaveTimer;

        // | Visual methods
        void highlightCurrentLine();
};