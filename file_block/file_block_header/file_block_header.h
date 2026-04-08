#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class FileBlockHeader: public QWidget 
{
    Q_OBJECT
    
    public:
        FileBlockHeader(QString name, QWidget* parent = nullptr);
        ~FileBlockHeader();

        void setHeader(QString name);

    private:
        QLabel* folderName;
};