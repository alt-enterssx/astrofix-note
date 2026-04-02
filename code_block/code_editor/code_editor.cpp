#include "code_editor.h"

CodeEditor::CodeEditor(Config* config, QWidget* parent): QPlainTextEdit(parent), config(config) {
    // | Config init
    if(!config) {
        qWarning() << "Error in init config";
    }

    // | Base settings
    this->setLineWrapMode(QPlainTextEdit::NoWrap);

}

void CodeEditor::saveCurrentFileMethod() {
    std::string saveText = this->toPlainText().toStdString();

    Config::Path path = this->config->getCurrentPath();
    if (path.type != Config::Path::PathType::FILE) { return; }

    QFile* file = new QFile(QString(path.path.c_str()));
    if (file->open(QFile::Text | QFile::WriteOnly | QFile::Truncate)) {
        file->write(saveText.c_str());
        file->close();
    }

}

CodeEditor::~CodeEditor() {}