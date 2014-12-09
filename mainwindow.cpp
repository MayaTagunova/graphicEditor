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

    connectActions();
    createContextMenu();
    createStatusBar();
    connect(ui->chooseColorButton, SIGNAL(clicked()),
            this, SLOT(chooseColor()));
    connect(ui->chooseFigureButton, SIGNAL(clicked()),
            this, SLOT(chooseStamp()));

    ToolFactory factory;
    ui->imageEdit->setTool(factory.createGenericBrush(Qt::black, Figure::ROUND, Size::SMALL));
}

void MainWindow::createContextMenu()
{
    ui->imageEdit->addAction(ui->actionUndo);
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

}

void MainWindow::createStatusBar()
{
    ui->statusbar->showMessage("");
}

bool MainWindow::canContinue()
{
    if (ui->imageEdit->canvas()->modified()) {
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

    setWindowModified(false);
    QString fileName = ui->imageEdit->canvas()->getFileName();
    if (fileName.isEmpty()) {
        fileName = "New image";
    }
    setWindowTitle(tr("%1[*] - %2")
                                  .arg(fileName)
                                  .arg(tr("Graphic editor")));

}

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
        ui->imageEdit->canvas()->clear();
        loadDataFromCanvas();
        update();
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
            ui->imageEdit->canvas()->setPath(path);
            if (!(ui->imageEdit->canvas()->readFile())) {
                QMessageBox::warning(this,
                                     tr("Warning"),
                                     tr("Failed to open file"),
                                     QMessageBox::Ok);
                ui->statusbar->showMessage(tr("Failed to open file"), DELAY);
            }
            loadDataFromCanvas();
        } else {
            ui->statusbar->showMessage(tr("File opening canceled"), DELAY);
        }
    }
}

bool MainWindow::saveImage()
{
    if (ui->imageEdit->canvas()->getPath() == "") {
        return saveImageAs();
    }
    if (ui->imageEdit->canvas()->writeFile()) {
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
        ui->imageEdit->canvas()->setPath(path);
        return saveImage();
        loadDataFromCanvas();
    }
    return false;
}

void MainWindow::undo()
{
    ui->imageEdit->canvas()->undo();
    update();
}

void MainWindow::showAbout()
{
    QMessageBox::about(this,
                       tr("About graphic editor"),
                       tr("Graphic Editor\n"
                          "Maya Tagunova, 2014"));
}

void MainWindow::switchToPencil(){}
void MainWindow::switchToBrush(){}
void MainWindow::switchToEraser(){}

void MainWindow::chooseColor()
{
    QColor newColor = QColorDialog::getColor(m_CurrentColor, this);

    if (newColor.isValid()) {
        m_CurrentColor = newColor;
    }
}

void MainWindow::chooseStamp()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
