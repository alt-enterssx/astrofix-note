#pragma once

#include <QSettings>
#include <cstdlib>

#define DEFAULT_FONT_SIZE 12

class Config 
{
    public:
        struct Path {
            enum PathType {
                FILE,
                FOLDER,
                UNKOWN
            };

            PathType type;
            std::string path;

            Path(PathType type, std::string path): type(type), path(path) {}
            Path() {}
        };

        Config(QSettings* settings);
        ~Config();

        // | Current path logic
        void setCurrentPath(Path* path);
        Path getCurrentPath();

        // | AutoSave logic
        void setAutoSaveSt(bool st);
        bool getAutoSaveSt();


        // | CodeEditor logic
        void setFontSize(int size);
        int getFontSize();

    private:
        QSettings* settings;
};