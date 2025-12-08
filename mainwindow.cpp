#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect actions to slots
    connect(ui->action_N, &QAction::triggered, this, &MainWindow::onNewFile);
    connect(ui->action_C, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(ui->action_S, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(ui->action_A, &QAction::triggered, this, &MainWindow::onSaveAsFile);
    connect(ui->action_X, &QAction::triggered, this, &MainWindow::onExit);
    connect(ui->action_C_2,  &QAction::triggered, this, &MainWindow::onCloseFile);
    connect(ui->action_U, &QAction::triggered, this, &MainWindow::onUndo);
    connect(ui->action_T, &QAction::triggered, this, &MainWindow::onCut);
    connect(ui->action_A_2,  &QAction::triggered, this, &MainWindow::onSelectAll);
    connect(ui->action_C_3, &QAction::triggered, this, &MainWindow::onCopy);
    connect(ui->action_P, &QAction::triggered, this, &MainWindow::onPaste);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewFile()
{
    ui->textEdit->clear();
    currentFile.clear();
    setWindowTitle("未命名 - 記事本");
}

void MainWindow::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("開啟檔案"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&file);
            ui->textEdit->setPlainText(in.readAll());
            currentFile = fileName;
            setWindowTitle(QFileInfo(fileName).fileName() + " - 記事本");
            file.close();
        } else {
            QMessageBox::warning(this, tr("錯誤"), tr("無法開啟檔案"));
        }
    }
}

void MainWindow::onSaveFile()
{
    if (currentFile.isEmpty()) {
        onSaveAsFile();
        return;
    }
    QFile file(currentFile);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        setWindowTitle(QFileInfo(currentFile).fileName() + " - 記事本");
        file.close();
    } else {
        QMessageBox::warning(this, tr("錯誤"), tr("無法儲存檔案"));
    }
}
void MainWindow::onCloseFile()
{
    ui->textEdit->clear();
    currentFile.clear();
    setWindowTitle("未命名 - 記事本");
}

void MainWindow::onSaveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存新檔"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        currentFile = fileName;
        onSaveFile();
    }
}

void MainWindow::onExit()
{
    close();
}

void MainWindow::onUndo()
{
    ui->textEdit->undo();
}

void MainWindow::onCut()
{
    ui->textEdit->cut();
}
void MainWindow::onSelectAll()
{
    ui->textEdit->selectAll();
}
void MainWindow::onCopy()
{
    ui->textEdit->copy();
}

void MainWindow::onPaste()
{
    ui->textEdit->paste();
}
