#include "file_block.h"

FileBlock::FileBlock(Config* config, QWidget* parent): QWidget(parent), config(config) {
    // | Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    this->setLayout(mainLayout);

    // | Header
    this->fileBlockHeader = new FileBlockHeader("");
    this->fileBlockHeader->setFixedHeight(30);
    mainLayout->addWidget(fileBlockHeader);

    // | Tree view
    QString path = QString(this->config->getCurrentPath().path.c_str());
    this->treeView = new QTreeView();
    
    mainLayout->addWidget(this->treeView);
    
    // | File model
    this->model = new QFileSystemModel();
    
    this->treeView->setModel(this->model);

    this->treeView->setHeaderHidden(true);
    this->treeView->hideColumn(1);
    this->treeView->hideColumn(2);
    this->treeView->hideColumn(3);
    this->treeView->hideColumn(4);
    
    QFileInfo info(path);

    // | Open file or directory
    if (info.isFile()) {
        QString dir = info.absolutePath();
        
        QModelIndex rootIndex = this->model->setRootPath(dir);
        this->treeView->setRootIndex(rootIndex);

        QModelIndex fileIndex = this->model->index(path);
        this->treeView->setCurrentIndex(fileIndex);
        this->treeView->scrollTo(fileIndex);

        QDir absoluteDir = info.absoluteDir();
        this->fileBlockHeader->setHeader(absoluteDir.dirName());
    } else if (info.isDir()) {
        QModelIndex rootIndex = this->model->setRootPath(path);
        this->treeView->setRootIndex(rootIndex);
        this->treeView->setCurrentIndex(rootIndex);

        this->treeView->expand(rootIndex);
        this->fileBlockHeader->setHeader(info.baseName());
    }

    // | Connects
    connect(this->treeView, &QTreeView::clicked, this, &FileBlock::onClicked);
    
    QTimer::singleShot(0, this, [this, path]() {
        emit selectFileToOpen(path);
    });
}

// | Open file of menubar
void FileBlock::openFile(QString path) {
    QFileInfo info(path);

    if (info.isFile()) {
        QString dir = info.absolutePath();
        
        QModelIndex rootIndex = this->model->setRootPath(dir);
        this->treeView->setRootIndex(rootIndex);

        QModelIndex fileIndex = this->model->index(path);
        this->treeView->setCurrentIndex(fileIndex);
        this->treeView->scrollTo(fileIndex);

        QDir absoluteDir = info.absoluteDir();
        this->fileBlockHeader->setHeader(absoluteDir.dirName());
    } else if (info.isDir()) {
        QModelIndex rootIndex = this->model->setRootPath(path);
        this->treeView->setRootIndex(rootIndex);
        this->treeView->setCurrentIndex(rootIndex);

        this->treeView->expand(rootIndex);
        this->fileBlockHeader->setHeader(info.baseName());
    }
}

// | Tree events
void FileBlock::onClicked(const QModelIndex& index) {
    QString path = this->model->filePath(index);
    QFileInfo info(path);

    if (info.isFile()) {
        emit selectFileToOpen(path);
    }
}

FileBlock::~FileBlock() {}