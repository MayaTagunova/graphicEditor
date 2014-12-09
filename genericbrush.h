#ifndef GENERICBRUSH_H
#define GENERICBRUSH_H

#include <QImage>
#include "tool.h"

class GenericBrush : public Tool
{
public:
    GenericBrush(const QImage &stamp);
    void apply(QImage* image, const QPoint& cursor);

private:
    QImage m_Stamp;

};

#endif // GENERICBRUSH_H
