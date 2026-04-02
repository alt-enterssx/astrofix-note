#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "../config/config.h"
#include "code_editor/code_editor.h"

class CodeBlock: public QWidget 
{
    Q_OBJECT

    public:
        CodeBlock(Config* config, QWidget* parent = nullptr);
        ~CodeBlock();

    public slots:
        // | Wrapped slots
        void saveCurrentFileWrapper();

    private:
        Config* config;
        CodeEditor* codeEditor;

};