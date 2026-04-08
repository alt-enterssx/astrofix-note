#include "code_editor.h"

namespace 
{

    struct Pair {
        QChar left;
        QChar right;
    };

    const Pair PAIRS[6] = {
        Pair{'{', '}'}, Pair{'(', ')'}, Pair{'"', '"'}, Pair{'\'', '\''},
        Pair{'`', '`'}, Pair{'[', ']'}
    };

    class AutoPair 
    {
        public:
            static bool isPair(QChar left, QChar right) {
                for (int i = 0; i < 6; i++) {
                    if (PAIRS[i].left == left && PAIRS[i].right == right) {
                        return true;
                    } 
                }
                return false;
            }
            static int getPair(QChar left) {
                for (int i = 0; i < 6; i++) {
                    if (PAIRS[i].left == left) {
                        return i;
                    }
                }
                return -1;
            }
    };
}

CodeEditor::CodeEditor(Config* config, QWidget* parent): QPlainTextEdit(parent), config(config), currentFile(nullptr) {
    // | Config init
    if(!config) {
        qWarning() << "Error in init config";
    }

    CodeEditor::highlightCurrentLine();

    // | Timers
    autoSaveTimer = new QTimer(this);
    autoSaveTimer->setSingleShot(true);

    // | Base settings
    this->setLineWrapMode(QPlainTextEdit::NoWrap);
    this->setUndoRedoEnabled(true);

    QPalette selectedTextPallete = this->palette();
    selectedTextPallete.setColor(QPalette::Highlight, QColor("#201c2a"));
    this->setPalette(selectedTextPallete);

    // | Connect plain text edit
    connect(this, &QPlainTextEdit::textChanged, this, &CodeEditor::onTextChanged);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    // | Connect timeers
    connect(autoSaveTimer, &QTimer::timeout, this, &CodeEditor::autoSaveMethod);

    // | Config set
    int fontSize = this->config->getFontSize();
    QFont font;
    font.setPointSize(fontSize);

    this->setFont(font);
}

// | KeyPress filters
void CodeEditor::keyPressEvent(QKeyEvent* event) {
    QTextCursor cursor = this->textCursor();

    if (event->modifiers() & (Qt::AltModifier | Qt::ControlModifier)) {
        return CodeEditor::modifiersFilter(&cursor, event);
    }
 
    switch(event->key()) {
        // | Add indent 
        case Qt::Key_Tab: {
            cursor.insertText(QString(4, ' '));
            return;
        }
        // | Delete auto pair and to spacing
        case Qt::Key_Backspace: {
            
            if (cursor.hasSelection()) { 
                QPlainTextEdit::keyPressEvent(event);
                return;
            }
                
            QString text = toPlainText();
            int pos = cursor.position();

            cursor.beginEditBlock();

            if (pos > 0 && pos < text.length()) {
                QChar left = text.at(pos - 1);
                QChar right = text.at(pos);
                
                if (AutoPair::isPair(left, right)) {

                    cursor.deletePreviousChar();
                    cursor.deleteChar();        

                    this->setTextCursor(cursor);

                    cursor.endEditBlock();

                    return;
                }
            }

            QTextBlock currentBlock = cursor.block();
            text = currentBlock.text();
            pos = cursor.positionInBlock();

            int allIndents = 0;
            while(pos - 1 - allIndents >= 0 && text.at(pos - 1 - allIndents) == ' ') {
                allIndents++;
            } 

            if (allIndents > 0) {
                if (allIndents % 4 != 0) {
                    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, allIndents % 4);
                    cursor.removeSelectedText();
                } else {
                    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 4);
                    cursor.removeSelectedText();
                }

                cursor.endEditBlock();
                return;
            }  

            cursor.endEditBlock();
            QPlainTextEdit::keyPressEvent(event);
            return;
        }
        case Qt::Key_Return: {
            if (cursor.hasSelection()) { 
                QPlainTextEdit::keyPressEvent(event);
                return;
            }
            
            QTextBlock block = cursor.block();
            QString text = block.text();

            int indent = 0;
            while (indent < text.length() && text.at(indent) == ' ') {
                indent++;
            }

            text = toPlainText();
            int pos = cursor.position();

            cursor.beginEditBlock();

            if (pos > 0 && pos < text.length()) {
                QChar left = text.at(pos - 1);
                QChar right = text.at(pos);
                
                if (AutoPair::isPair(left, right)) {
                    cursor.insertBlock();
                    cursor.insertBlock();
                    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
                    cursor.insertText(QString(indent, ' '));

                    cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
                    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);

                    cursor.insertText(QString(indent + 4, ' '));

                    this->setTextCursor(cursor);

                    cursor.endEditBlock();
                    return;
                }
            }

            cursor.insertBlock();
            cursor.insertText(QString(indent, ' '));
            this->setTextCursor(cursor);

            cursor.endEditBlock();
            return;
        }
        case Qt::Key_Home: {
            cursor.setPosition(0);
            this->setTextCursor(cursor);
            return;
        }  
        case Qt::Key_End: {
            QString codeText = this->toPlainText();
            cursor.setPosition(codeText.length());
            this->setTextCursor(cursor);
            return;
        }
    }

    if (!event->text().isEmpty() && event->text().length() == 1) {
        return CodeEditor::charsFilter(&cursor, event->text().at(0), event);
    }
    
    QPlainTextEdit::keyPressEvent(event);
    return;
}

void CodeEditor::charsFilter(QTextCursor* cursor, QChar sym, QKeyEvent* event) {
    int pairIndx = AutoPair::getPair(sym);

    if (pairIndx == -1) {
        QPlainTextEdit::keyPressEvent(event);
        return;
    }
    if (cursor->hasSelection()) {
        cursor->beginEditBlock();

        QString selectedText = cursor->selectedText();
        cursor->setPosition(cursor->selectionEnd());
        
        cursor->insertText(PAIRS[pairIndx].right);
        cursor->movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, selectedText.length() + 1);
        cursor->insertText(PAIRS[pairIndx].left);
        cursor->movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, selectedText.length() + 1);


        cursor->endEditBlock();

        this->setTextCursor(*cursor);
        return;
    }

    cursor->insertText(QString(PAIRS[pairIndx].left) + PAIRS[pairIndx].right);
    cursor->movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);

    this->setTextCursor(*cursor);

    return;
}

void CodeEditor::modifiersFilter(QTextCursor* cursor, QKeyEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        switch(event->key()) {
            case Qt::Key_Equal: {
                QFont font = this->font();
                qDebug() << font.pointSize();
                int fontSize = font.pointSize();
                fontSize += 2;
                
                if (fontSize >= 6 && fontSize <= 35) {
                    font.setPointSize(fontSize);
                    qDebug() << font.pointSize();
    
                    this->setFont(font);
                    this->config->setFontSize(fontSize);
                }

                return;
            }
            case Qt::Key_Minus: {
                QFont font = this->font();
                qDebug() << font.pointSize();
                int fontSize = font.pointSize();
                fontSize -= 2;
                
                if (fontSize >= 6 && fontSize <= 35) {
                    font.setPointSize(fontSize);
                    qDebug() << font.pointSize();
    
                    this->setFont(font);
                    this->config->setFontSize(fontSize);
                }

                return;
            }
            case Qt::Key_C: {
                return CodeEditor::copyHandle();
            }
            case Qt::Key_V: {
                return CodeEditor::pasteHandle();
            }
            case Qt::Key_X: {
                return CodeEditor::cutHandle();
            }
            case Qt::Key_A: {
                return CodeEditor::selectAllHandle();
            }
        }
    }

    return QPlainTextEdit::keyPressEvent(event);
}

// | Context menu event
void CodeEditor::contextMenuEvent(QContextMenuEvent* event) {
    QMenu* contextMenu = new QMenu(this);
    QAction* undoAction = contextMenu->addAction("Undo", this, &QPlainTextEdit::undo);
    QAction* redoAction = contextMenu->addAction("Redo", this, &QPlainTextEdit::redo);

    contextMenu->addSeparator();

    QAction* copyAction = contextMenu->addAction("Copy", this, &CodeEditor::copyHandle);
    QAction* pasteAction = contextMenu->addAction("Paste", this, &CodeEditor::pasteHandle);
    QAction* cutAction = contextMenu->addAction("Cut", this, &CodeEditor::cutHandle);
    QAction* selectAllAction = contextMenu->addAction("Select All", this, &CodeEditor::selectAllHandle);

    QAction* selected = contextMenu->exec(event->globalPos());
}

// | File works
void CodeEditor::saveCurrentFileMethod() {
    QString saveText = this->toPlainText();

    if (!this->currentFile) {
        Config::Path path = this->config->getCurrentPath();

        if (path.type != Config::Path::PathType::FILE) {
            return;
        }

        this->currentFile = new QFile(QString::fromStdString(path.path));
    }

    if (!this->currentFile->isOpen()) {
        if (!this->currentFile->open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
            return;
        }
    }

    this->currentFile->resize(0);
    this->currentFile->write(saveText.toUtf8());
    this->currentFile->flush(); 
}

void CodeEditor::openFileMethod(QString path) {
    QFileInfo fileInfo(path);

    if (fileInfo.isDir()) { return; }

    QFile* tmp = new QFile(path);
    if (tmp->open(QFile::Text | QFile::ReadWrite)) {
        if (this->currentFile != nullptr) {
            this->currentFile->close();
        }

        this->currentFile = tmp;
        
        QString readed = this->currentFile->readAll();
        this->currentFile->close();

        this->setPlainText(readed);
    }
}

// | Slots for signals
void CodeEditor::onTextChanged() {
    this->autoSaveTimer->start(1000);
}

// | Slots for timers
void CodeEditor::autoSaveMethod() {
    if (this->config->getAutoSaveSt()) {
        return CodeEditor::saveCurrentFileMethod();
    }
}

// | Modifiers methods
void CodeEditor::copyHandle() {
    QTextCursor cursor = this->textCursor();
    if (cursor.hasSelection()) {
        return QPlainTextEdit::copy();
    }

    cursor.select(QTextCursor::BlockUnderCursor);
    QString copyLine = cursor.selectedText();

    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(copyLine);

    return;
}

void CodeEditor::pasteHandle() {
    QTextCursor cursor = this->textCursor();
    if (cursor.hasSelection()) {
        return QPlainTextEdit::paste();
    }

    QClipboard* clipboard = QGuiApplication::clipboard();
    QString pastedLine;

    if (clipboard->text().isEmpty()) { return; }

    if (cursor.position() == 0 || cursor.positionInBlock() == 0) {
        pastedLine = clipboard->text() + "\n";
    } else if (cursor.positionInBlock() > 0) {
        pastedLine = clipboard->text();
    }

    cursor.insertText(pastedLine);
    return;
}

void CodeEditor::cutHandle() {
    QTextCursor cursor = this->textCursor();
    if (cursor.hasSelection()) {
        return QPlainTextEdit::cut();
    }

    cursor.beginEditBlock();

    cursor.select(QTextCursor::BlockUnderCursor);
    QString cutLine = cursor.selectedText();

    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(cutLine);

    cursor.removeSelectedText();
    cursor.deleteChar();

    cursor.endEditBlock();

    return;
}

void CodeEditor::selectAllHandle() {
    QTextCursor cursor = this->textCursor();
    if (cursor.hasSelection()) {
        return QPlainTextEdit::selectAll();
    }

    this->selectAll();
    return;
}

// | Visuals method
void CodeEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!this->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor("#1c1926");

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);

        selection.cursor = this->textCursor();
        selection.cursor.clearSelection();

        extraSelections.append(selection);
    }

    this->setExtraSelections(extraSelections);
}

CodeEditor::~CodeEditor() {}