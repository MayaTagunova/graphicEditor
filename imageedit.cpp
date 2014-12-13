#include "imageedit.h"
#include <math.h>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

ImageEdit::ImageEdit(QWidget *parent) :
    QWidget(parent),
    m_Canvas(new Canvas()),
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
        drawLine(m_CurrentPoint, event->pos());
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
        drawLine(m_CurrentPoint, event->pos());
        update();
        m_Canvas->setModified();
        m_Drawing = false;
    }
}

void ImageEdit::drawLine(const QPoint startPoint, const QPoint endPoint)
{
    int xCurr = startPoint.x();
    int yCurr = startPoint.y();
    int xNew = endPoint.x();
    int yNew = endPoint.y();

    double tangent = 0;

    if (abs(xNew - xCurr) > abs(yNew - yCurr)) {
        if (xNew != xCurr) {

            tangent = (double)(yNew - yCurr) /
                      (double)(xNew - xCurr);
        }
        for (int x = std::min(xCurr, xNew);
                 x <= std::max(xCurr, xNew);
                 x++) {

            int y = (int) (tangent * (x - xCurr)) + yCurr;
            m_Tool->apply(m_Canvas->getImage(), QPoint(x, y));
        }
    } else {
        if (yNew != yCurr) {

            tangent = (double)(xNew - xCurr) /
                      (double)(yNew - yCurr);
        }
        for (int y = std::min(yCurr, yNew);
                 y <= std::max(yCurr, yNew);
                 y++) {

            int x = round (tangent * (y - yCurr) + xCurr);
            m_Tool->apply(m_Canvas->getImage(), QPoint(x, y));
        }
    }

    m_CurrentPoint = endPoint;
}

void ImageEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rectangle = event->rect();
    painter.drawImage(rectangle, *(m_Canvas->getImage()), rectangle);
}
