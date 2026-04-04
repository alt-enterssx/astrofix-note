#include "config.h"

Config::Config(QSettings* settings): settings(settings) {
    if (!settings) {
        qWarning() << "Error in init settings";
    }
}

// | Current path logic
void Config::setCurrentPath(Config::Path* path) {
    this->settings->setValue("/application/current-path/path", QString(path->path.c_str()));
    this->settings->setValue("/application/current-path/type", (path->type == Config::Path::PathType::FILE) ? "file" 
        : (path->type == Config::Path::PathType::FOLDER) ? "folder" : "unkown" );
}

Config::Path Config::getCurrentPath() {
    Config::Path path = Config::Path();

    path.path = this->settings->value("/application/current-path/path").toString().toStdString();
    std::string pathTypeStr = this->settings->value("/application/current-path/type").toString().toStdString();

    path.type = (pathTypeStr == "file") ? Config::Path::PathType::FILE 
        : (pathTypeStr == "folder") ? Config::Path::PathType::FOLDER : Config::Path::PathType::UNKOWN;  

    return path;
}

// | AutoSave logic
void Config::setAutoSaveSt(bool st) {
    this->settings->setValue("/application/file-config/autosave", st);
}

bool Config::getAutoSaveSt() {
    return this->settings->value("/application/file-config/autosave").toBool();
}


// | CodeEditor logic
void Config::setFontSize(int size) {
    this->settings->setValue("/code_editor/font_size", size);
}

int Config::getFontSize() {
    return this->settings->value("/code_editor/font_size", DEFAULT_FONT_SIZE).toInt();
}

Config::~Config() {}