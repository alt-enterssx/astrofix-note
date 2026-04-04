#pragma once

#include <QMainWindow>
#include <QScreen>
#include <QGuiApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>

#include "menubar/menubar.h"
#include "code_block/code_block.h"
#include "config/config.h"

class Win: public QMainWindow 
{
    Q_OBJECT

    public:
        Win(QWidget* parent = nullptr);
        ~Win();

    private slots:
        // | MenuBar slots
        void openFullScreen(QPushButton* fullScreenBtn);
        void hideApplication();

    private: 
        // | Widgets
        MenuBar* menuBar;
        CodeBlock* codeBlock;
};