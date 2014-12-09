#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H

#include "genericbrush.h"
#include <QColor>

#define STAMP_SIZE 31
#define TRANSPARENT 0x00FFFFFF

enum class Figure {ROUND, SQUARE, SLASH, BACKSLASH};
enum class Size : int {SMALL = 3, MEDIUM = 5, LARGE = 8};

class ToolFactory
{
public:
    ToolFactory();
    Tool* createGenericBrush(QColor color, Figure figure, Size size);
};

#endif // TOOLFACTORY_H
