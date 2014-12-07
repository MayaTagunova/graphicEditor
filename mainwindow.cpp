#include <QtGui>
#include <QCloseEvent>
#include "mainwindow.h"
#include "ui_graphiceditor.h"

#define DELAY 2000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createContextMenu();
    connectActions();
    createStatusBar();
//    loadDataFromCanvas();
//    connect(ui->textEdit, SIGNAL(textChanged()),
//            this, SLOT(updateModelAndTitle()));
}

void MainWindow::createContextMenu()
{
    //ui->imageEdit->addAction(ui->actionUndo);
}

void MainWindow::connectActions()
{
    connect(ui->actionNew, SIGNAL(triggered()),
            this, SLOT(createNewImage()));
    connect(ui->actionOpen, SIGNAL(triggered()),
            this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()),
            this, SLOT(saveImage()));
    connect(ui->actionSaveAs, SIGNAL(triggered()),
            this, SLOT(saveImageAs()));
    connect(ui->actionQuit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->actionUndo, SIGNAL(triggered()),
            this, SLOT(undo()));
    connect(ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(showAbout()));
    connect(ui->actionPencil, SIGNAL(triggered()),
            this, SLOT(switchToPencil()));
    connect(ui->actionBrush, SIGNAL(triggered()),
            this, SLOT(switchToBrush()));
    connect(ui->actionEraser, SIGNAL(triggered()),
            this, SLOT(switchToEraser()));
    connect(ui->actionChooseColor, SIGNAL(triggered()),
            this, SLOT(chooseColor()));
    connect(ui->actionChooseStamp, SIGNAL(triggered()),
            this, SLOT(chooseStamp()));
}

void MainWindow::createStatusBar()
{
    ui->statusbar->showMessage("");
}

bool MainWindow::canContinue()
{
    if (image.modified()) {
        int a;
        a = QMessageBox::warning(this,
                                 tr("Warning"),
                                 tr("The image has been modified.\n"
                                    "Do you want to save your changes?"),
                                 QMessageBox::Yes,
                                 QMessageBox::No,
                                 QMessageBox::Cancel);
        if (a == QMessageBox::Yes) {
            return saveImageAs();
        } else if (a == QMessageBox::Cancel) {
            ui->statusbar->showMessage(tr("File saving canceled"), DELAY);
            return false;
        }
    }
    return true;
}

void MainWindow::loadDataFromCanvas()
{
//    ui->textEdit->setText(model.getText());
    setWindowModified(false);
    QString fileName = image.getFileName();
    if (fileName.isEmpty()) {
        fileName = "New image";
    }
    setWindowTitle(tr("%1[*] - %2")
                                  .arg(fileName)
                                  .arg(tr("Graphic editor")));

}
/*
void MainWindow::updateModelAndTitle()
{
    if (updated == true) {
        updated = false;
    } else {
        model.setText(ui->textEdit->toPlainText());
        setWindowModified(true);
    }
}*/

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (canContinue()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::createNewImage()
{
    if (canContinue()) {
        image.clear();
        loadDataFromCanvas();
    }
}

void MainWindow::openFile()
{
    if (canContinue()) {
        QString path = QFileDialog::getOpenFileName(this,
                                                        tr("File dialog"),
                                                        ".",
                                                        tr("Any files (*)"));
        if (path != "") {
            image.setPath(path);
            if (!(image.readFile())) {
                QMessageBox::warning(this,
                                     tr("Warning"),
                                     tr("Failed to open file"),
                                     QMessageBox::Ok);
                ui->statusbar->showMessage(tr("Failed to open file"), DELAY);
            }
            //updated = true;
            loadDataFromCanvas();
        } else {
            ui->statusbar->showMessage(tr("File opening canceled"), DELAY);
        }
    }
}

bool MainWindow::saveImage()
{
    if (image.getPath() == "") {
        return saveImageAs();
    }
    if (image.writeFile()) {
        ui->statusbar->showMessage(tr("The image was saved"), DELAY);
        setWindowModified(false);
        return true;
    } else {
        QMessageBox::warning(this,
                             tr("Warning"),
                             tr("Failed to save image"),
                             QMessageBox::Ok);
        ui->statusbar->showMessage(tr("Failed to save image"), DELAY);
        return false;
    }
}

bool MainWindow::saveImageAs()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("File dialog"),
                                                ".",
                                                tr("Any files (*)"));
    if (path != "") {
        image.setPath(path);
        return saveImage();
        loadDataFromCanvas();
    }
    return false;
}

void MainWindow::undo(){}

void MainWindow::showAbout()
{
    QMessageBox::about(this,
                       tr("About graphic editor"),
                       tr("Text Editor 1.0\n"
                          "Maya Tagunova, 2014"));
}

void MainWindow::switchToPencil(){}
void MainWindow::switchToBrush(){}
void MainWindow::switchToEraser(){}
void MainWindow::chooseColor(){}
void MainWindow::chooseStamp(){}

MainWindow::~MainWindow()
{
    delete ui;
}
