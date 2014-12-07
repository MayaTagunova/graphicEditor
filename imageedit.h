#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H

#include <QWidget>

class ImageEdit : public QWidget
{
    Q_OBJECT
public:
    explicit ImageEdit(QWidget *parent = 0);

protected:
    void mouseMoveEvent (QMouseEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent *event);

private:
    QImage m_Image;
    bool m_Modified;

signals:

public slots:
};

#endif // IMAGEEDIT_H
