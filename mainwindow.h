#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Canvas image;

    void createContextMenu();
    void connectActions();
    void createStatusBar();
    void closeEvent(QCloseEvent *);

    bool canContinue();

private slots:
    void createNewImage();
    void openFile();
    bool saveImage();
    bool saveImageAs();
    void undo();
    void showAbout();
    void switchToPencil();
    void switchToBrush();
    void switchToEraser();
    void chooseColor();
    void chooseStamp();

    void loadDataFromCanvas();
//    void updateModelAndTitle();
};

#endif // MAINWINDOW_H
