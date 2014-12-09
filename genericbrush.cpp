#include <QPainter>
#include "genericbrush.h"
#include "toolfactory.h"

GenericBrush::GenericBrush(const QImage& stamp) :
    m_Stamp(stamp)
{

}

void GenericBrush::apply(QImage* image, const QPoint& currentPoint)
{
    int stampCenter = (STAMP_SIZE - 1) / 2;

    QPainter painter(image);
    QPoint newPoint(currentPoint.x() - stampCenter,
                    currentPoint.y() - stampCenter);

    painter.drawImage(newPoint, m_Stamp);
}
