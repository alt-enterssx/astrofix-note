#include "code_block.h"

CodeBlock::CodeBlock(Config* config, QWidget* parent): QWidget(parent), config(config) {
    // | Config init
    if(!config) {
        qWarning() << "Error in init config";
    }

    // | Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    this->setLayout(mainLayout);

    // | Code editor widget
    this->codeEditor = new CodeEditor(config);
    mainLayout->addWidget(codeEditor);
}

// | Wrapped slots
void CodeBlock::saveCurrentFileWrapper() { this->codeEditor->saveCurrentFileMethod(); }

CodeBlock::~CodeBlock() {}