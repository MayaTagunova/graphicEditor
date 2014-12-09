#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H

#include <QWidget>
#include <memory>
#include "canvas.h"
#include "toolfactory.h"

class ImageEdit : public QWidget
{
    Q_OBJECT
public:
    explicit ImageEdit(QWidget *parent = 0);

    void setTool(Tool *newTool);
    std::shared_ptr<Canvas> canvas();

protected:
    void mouseMoveEvent (QMouseEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    std::shared_ptr<Canvas> m_Canvas;
    std::unique_ptr<Tool> m_Tool;

    bool m_Drawing;
    QPoint m_CurrentPoint;

signals:
    void drawingPointChanged(const QPoint&);

public slots:
};

#endif // IMAGEEDIT_H
