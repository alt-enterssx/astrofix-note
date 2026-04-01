#pragma once
#include <QMainWindow>

class Win: public QMainWindow 
{
    Q_OBJECT

    public:
        Win(QWidget* parent = nullptr);
        ~Win();
};