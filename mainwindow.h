#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas.h"
#include "toolfactory.h"

enum class Figure;
enum class Size;
enum class Type {PENCIL, BRUSH, ERASER};

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
    QWidget *m_StampMenu;

    ToolFactory m_Factory;

    QColor m_Color;
    Figure m_Figure;
    Size m_Size;
    Type m_Type;


    void createMenus();
    void connectActions();
    void createStatusBar();
    void closeEvent(QCloseEvent *);
    bool canContinue();
    void updateColorIcon();
    void updateStampIcon();
    void setStamp();

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
    void updateImageName();

    void roundMedium();
    void roundLarge();
    void squareMedium();
    void squareLarge();
    void slashMedium();
    void slashLarge();
    void backSlashMedium();
    void backSlashLarge();
};

#endif // MAINWINDOW_H
