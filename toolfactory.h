#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H

#include "genericbrush.h"
#include <QColor>

#define STAMP_SIZE 17
#define TRANSPARENT 0x00FFFFFF

enum class Figure {ROUND, SQUARE, SLASH, BACKSLASH};
enum class Size : int {PENCIL = 1, MEDIUM_BRUSH = 5, LARGE_BRUSH= 8};

class ToolFactory
{
public:
    ToolFactory();
    QImage createStamp(QColor color, Figure figure, Size size);
    Tool* createGenericBrush(QColor color, Figure figure, Size size);

private:
    QImage m_Stamp;
};

#endif // TOOLFACTORY_H
