#include <QtGui>
#include <QCloseEvent>
#include <QActionGroup>
#include "mainwindow.h"
#include "ui_graphiceditor.h"

#define DELAY 2000
#define ICON_SIZE 16

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_StampMenu(nullptr),
    m_Color(Qt::black),
    m_Figure(Figure::ROUND),
    m_Size(Size::PENCIL),
    m_Type(Type::PENCIL)
{
    ui->setupUi(this);

    connectActions();
    createMenus();
    createStatusBar();

    connect(ui->pencilButton, SIGNAL(clicked()),
            this, SLOT(switchToPencil()));
    connect(ui->brushButton, SIGNAL(clicked()),
            this, SLOT(switchToBrush()));
    connect(ui->eraserButton, SIGNAL(clicked()),
            this, SLOT(switchToEraser()));
    connect(ui->chooseColorButton, SIGNAL(clicked()),
            this, SLOT(chooseColor()));
    connect(ui->chooseFigureButton, SIGNAL(clicked()),
            this, SLOT(chooseStamp()));

    QButtonGroup* toolsButtonGroup = new QButtonGroup(this);

    toolsButtonGroup->addButton(ui->pencilButton);
    toolsButtonGroup->addButton(ui->brushButton);
    toolsButtonGroup->addButton(ui->eraserButton);

    switchToPencil();
    updateColorIcon();
    adjustSize();
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
}

void MainWindow::createStatusBar()
{
    ui->statusbar->showMessage("");
}

void MainWindow::createMenus()
{
    ui->imageEdit->addAction(ui->actionUndo);

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

void MainWindow::updateColorIcon()
{
    QPixmap icon(ICON_SIZE, ICON_SIZE);
    icon.fill(m_Color);
    ui->chooseColorButton->setIcon(icon);
}

void MainWindow::updateImageName()
{
    QString fileName = ui->imageEdit->canvas()->getFileName();
    if (fileName.isEmpty()) {
        fileName = "New image";
    }
    setWindowTitle(tr("%1[*] - %2")
                                  .arg(fileName)
                                  .arg(tr("Graphic editor")));

}

void MainWindow::updateStampIcon()
{
    QColor color;
    if (m_Type == Type::ERASER)
        color = Qt::white;
    else
        color = m_Color;
    ui->chooseFigureButton->setIcon(QPixmap::fromImage(
                                            m_Factory.createStamp(color,
                                                                  m_Figure,
                                                                  m_Size)));
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
        updateImageName();
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
            setWindowModified(false);
            ui->imageEdit->setFixedHeight(ui->imageEdit->canvas()->getHeight());
            ui->imageEdit->setFixedWidth(ui->imageEdit->canvas()->getWidth());
            update();
            updateImageName();
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
        updateImageName();
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

void MainWindow::switchToPencil()
{
    ui->imageEdit->setTool(m_Factory.createGenericBrush(m_Color,
                                                        Figure::ROUND,
                                                        Size::PENCIL));
    m_Type = Type::PENCIL;
    ui->chooseColorButton->setEnabled(true);
    ui->chooseFigureButton->setEnabled(false);
    updateStampIcon();
}

void MainWindow::switchToBrush()
{
    if (m_Type == Type::PENCIL)
        m_Size = Size::MEDIUM_BRUSH;
    ui->imageEdit->setTool(m_Factory.createGenericBrush(m_Color,
                                                        m_Figure,
                                                        m_Size));
    m_Type = Type::BRUSH;
    ui->chooseColorButton->setEnabled(true);
    ui->chooseFigureButton->setEnabled(true);
    updateStampIcon();
}

void MainWindow::switchToEraser()
{
    ui->imageEdit->setTool(m_Factory.createGenericBrush(Qt::white,
                                                        m_Figure,
                                                        m_Size));
    m_Type = Type::ERASER;
    ui->chooseColorButton->setEnabled(false);
    ui->chooseFigureButton->setEnabled(true);
    updateStampIcon();
}

void MainWindow::chooseColor()
{
    QColor newColor = QColorDialog::getColor(m_Color, this);

    if (newColor.isValid()) {
        m_Color = newColor;
        ui->imageEdit->setTool(m_Factory.createGenericBrush(m_Color,
                                                            m_Figure,
                                                            m_Size));
        updateColorIcon();
    }
}

void MainWindow::chooseStamp()
{
    if (m_StampMenu != nullptr) {
        return;
    }
    m_StampMenu = new QWidget(this, Qt::Popup);

    QIcon icon;
    QColor color;
    if (m_Type == Type::ERASER)
        color = Qt::white;
    else
        color = m_Color;

    QPushButton *roundMedium = new QPushButton;
    roundMedium->setCheckable(true);
    icon.addPixmap(QPixmap::fromImage(m_Factory.createStamp(color,
                                                    Figure::ROUND,
                                                    Size::MEDIUM_BRUSH)
                                      ));
    roundMedium->setIcon(icon);
    connect(roundMedium, SIGNAL(clicked()),
            this, SLOT(roundMedium()));

    QPushButton *roundLarge = new QPushButton;
    roundLarge->setCheckable(true);
    icon.addPixmap(QPixmap::fromImage(m_Factory.createStamp(color,
                                                            Figure::ROUND,
                                                            Size::LARGE_BRUSH)
                                      ));
    roundLarge->setIcon(icon);
    connect(roundLarge, SIGNAL(clicked()),
            this, SLOT(roundLarge()));

    QPushButton *squareMedium = new QPushButton;
    squareMedium->setCheckable(true);
    icon.addPixmap(QPixmap::fromImage(m_Factory.createStamp(color,
                                                            Figure::SQUARE,
                                                            Size::MEDIUM_BRUSH)
                                      ));
    squareMedium->setIcon(icon);
    connect(squareMedium, SIGNAL(clicked()),
            this, SLOT(squareMedium()));

    QPushButton *squareLarge = new QPushButton;
    squareLarge->setCheckable(true);
    icon.addPixmap(QPixmap::fromImage(m_Factory.createStamp(color,
                                                            Figure::SQUARE,
                                                            Size::LARGE_BRUSH)
                                      ));
    squareLarge->setIcon(icon);
    connect(squareLarge, SIGNAL(clicked()),
            this, SLOT(squareLarge()));

    QPushButton *slashMedium = new QPushButton;
    slashMedium->setCheckable(true);
    icon.addPixmap(QPixmap::fromImage(m_Factory.createStamp(color,
                                                            Figure::SLASH,
                                                            Size::MEDIUM_BRUSH)
                                      ));
    slashMedium->setIcon(icon);
    connect(slashMedium, SIGNAL(clicked()),
            this, SLOT(slashMedium()));

    QPushButton *slashLarge = new QPushButton;
    slashLarge->setCheckable(true);
    icon.addPixmap(QPixmap::fromImage(m_Factory.createStamp(color,
                                                            Figure::SLASH,
                                                            Size::LARGE_BRUSH)
                                      ));
    slashLarge->setIcon(icon);
    connect(slashLarge, SIGNAL(clicked()),
            this, SLOT(slashLarge()));

    QPushButton *backSlashMedium = new QPushButton;
    backSlashMedium->setCheckable(true);
    icon.addPixmap(QPixmap::fromImage(m_Factory.createStamp(color,
                                                            Figure::BACKSLASH,
                                                            Size::MEDIUM_BRUSH)
                                      ));
    backSlashMedium->setIcon(icon);
    connect(backSlashMedium, SIGNAL(clicked()),
            this, SLOT(backSlashMedium()));

    QPushButton *backSlashLarge = new QPushButton;
    backSlashLarge->setCheckable(true);
    icon.addPixmap(QPixmap::fromImage(m_Factory.createStamp(color,
                                                            Figure::BACKSLASH,
                                                            Size::LARGE_BRUSH)
                                      ));
    backSlashLarge->setIcon(icon);
    connect(backSlashLarge, SIGNAL(clicked()),
            this, SLOT(backSlashLarge()));

    QButtonGroup *brushGroup = new QButtonGroup(m_StampMenu);

    brushGroup->addButton(roundMedium);
    brushGroup->addButton(roundLarge);
    brushGroup->addButton(squareMedium);
    brushGroup->addButton(squareLarge);
    brushGroup->addButton(slashMedium);
    brushGroup->addButton(slashLarge);
    brushGroup->addButton(backSlashMedium);
    brushGroup->addButton(backSlashLarge);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(roundMedium, 0, 0);
    layout->addWidget(roundLarge, 0, 1);
    layout->addWidget(squareMedium, 1, 0);
    layout->addWidget(squareLarge, 1, 1);
    layout->addWidget(slashMedium, 2, 0);
    layout->addWidget(slashLarge, 2, 1);
    layout->addWidget(backSlashMedium, 3, 0);
    layout->addWidget(backSlashLarge, 3, 1);

    m_StampMenu->setLayout(layout);

    QRect rect = ui->chooseFigureButton->geometry();
    QPoint point = mapToGlobal(rect.topRight());

    m_StampMenu->move(point);
    m_StampMenu->show();

}

void MainWindow::setStamp()
{
    QColor color;
    if (m_Type == Type::ERASER)
        color = Qt::white;
    else
        color = m_Color;
    ui->imageEdit->setTool(m_Factory.createGenericBrush(color,
                                                        m_Figure,
                                                        m_Size));
    if (m_StampMenu != nullptr)
        delete m_StampMenu;
    m_StampMenu = nullptr;
    updateStampIcon();
}

void MainWindow::roundMedium()
{
    m_Figure = Figure::ROUND;
    m_Size = Size::MEDIUM_BRUSH;
    setStamp();
}

void MainWindow::roundLarge()
{
    m_Figure = Figure::ROUND;
    m_Size = Size::LARGE_BRUSH;
    setStamp();
}

void MainWindow::squareMedium()
{
    m_Figure = Figure::SQUARE;
    m_Size = Size::MEDIUM_BRUSH;
    setStamp();

}

void MainWindow::squareLarge()
{
    m_Figure = Figure::SQUARE;
    m_Size = Size::LARGE_BRUSH;
    setStamp();
}

void MainWindow::slashMedium()
{
    m_Figure = Figure::SLASH;
    m_Size = Size::MEDIUM_BRUSH;
    setStamp();
}

void MainWindow::slashLarge()
{
    m_Figure = Figure::SLASH;
    m_Size = Size::LARGE_BRUSH;
    setStamp();
}

void MainWindow::backSlashMedium()
{
    m_Figure = Figure::BACKSLASH;
    m_Size = Size::MEDIUM_BRUSH;
    setStamp();
}

void MainWindow::backSlashLarge()
{
    m_Figure = Figure::BACKSLASH;
    m_Size = Size::LARGE_BRUSH;
    setStamp();
}

MainWindow::~MainWindow()
{
    delete ui;
}
