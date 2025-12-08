#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewFile();
    void onOpenFile();
    void onSaveFile();
    void onSaveAsFile();
    void onExit();
    void onUndo();
    void onCut();
    void onSelectAll();
    void onCloseFile();
    void onCopy();
    void onPaste();

private:
    Ui::MainWindow *ui;
    QString currentFile;
};

#endif // MAINWINDOW_H
