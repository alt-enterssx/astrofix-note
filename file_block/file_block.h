#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTreeView>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QModelIndex>
#include <QTimer>

#include "../config/config.h"
#include "file_block_header/file_block_header.h"

class FileBlock: public QWidget 
{
    Q_OBJECT

    public:
        FileBlock(Config* config, QWidget* parent = nullptr);
        ~FileBlock();

    public slots:
        // | Open file of menubar
        void openFile(QString path);

    signals: 
        void selectFileToOpen(QString path);

    private slots: 
        // | Tree events
        void onClicked(const QModelIndex& index);

    private:
        // | Config
        Config* config;

        // | Widgets
        QFileSystemModel* model;
        QTreeView* treeView;
        FileBlockHeader* fileBlockHeader;
};