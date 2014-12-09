#ifndef TOOL_H
#define TOOL_H

#include <QImage>

class Tool
{
public:
    virtual void apply(QImage*, const QPoint&) = 0;
};

#endif // TOOL_H
