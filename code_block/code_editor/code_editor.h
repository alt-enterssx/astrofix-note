#pragma once

#include <QPlainTextEdit>
#include <QFile>
#include <cstdlib>

#include "../../config/config.h"

class CodeEditor: public QPlainTextEdit 
{
    Q_OBJECT

    public:
        CodeEditor(Config* config, QWidget* parent = nullptr);
        ~CodeEditor();
 
    public slots: 
        void saveCurrentFileMethod();

    private:
        Config* config;

};