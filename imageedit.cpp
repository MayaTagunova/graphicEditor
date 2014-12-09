#include "imageedit.h"
#include <QMouseEvent>
#include <QPainter>

ImageEdit::ImageEdit(QWidget *parent) :
    QWidget(parent),
    m_Canvas(new Canvas()),
    //m_Tool(tool),
    m_Drawing(false),
    m_CurrentPoint()
{
    setAttribute(Qt::WA_StaticContents);
}

void ImageEdit::setTool(Tool *newTool)
{
    m_Tool.reset(newTool);
}

std::shared_ptr<Canvas> ImageEdit::canvas()
{
    return m_Canvas;
}

void ImageEdit::mouseMoveEvent (QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && m_Drawing) {

        m_Tool->apply(m_Canvas->getImage(), event->pos());
        update();
    }
}

void ImageEdit::mousePressEvent (QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_CurrentPoint = event->pos();
        m_Canvas->storeImage();
        m_Drawing = true;
    }
}

void ImageEdit::mouseReleaseEvent (QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_Drawing) {
        m_Tool->apply(m_Canvas->getImage(), event->pos());
        update();
        m_Canvas->setModified();
        m_Drawing = false;
    }
}


void ImageEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rectangle = event->rect();
    painter.drawImage(rectangle, *(m_Canvas->getImage()), rectangle);
}


