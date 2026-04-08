#include "file_block_header.h"

FileBlockHeader::FileBlockHeader(QString name, QWidget* parent): QWidget(parent) {
    this->setObjectName("headerFileBlock");
    this->setAttribute(Qt::WA_StyledBackground, true);    
    
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(15, 0, 15, 0);
    mainLayout->setSpacing(0);

    this->folderName = new QLabel(name);
    mainLayout->addWidget(folderName);
}

void FileBlockHeader::setHeader(QString name) {
    this->folderName->setText(name);
}

FileBlockHeader::~FileBlockHeader() {}