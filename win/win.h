#pragma once

#include <QMainWindow>
#include <QScreen>
#include <QGuiApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "menubar/menubar.h"

class Win: public QMainWindow 
{
    Q_OBJECT

    public:
        Win(QWidget* parent = nullptr);
        ~Win();

    private slots:
        // | MenuBar slots
        void openFullScreen();
        void hideApplication();

    private: 
        // | Widgets
        MenuBar* menuBar;

};