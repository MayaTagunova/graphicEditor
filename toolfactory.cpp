#include "toolfactory.h"
#include <math.h>
#include <QImage>
#include <QPoint>

ToolFactory::ToolFactory()
{

}

static bool isInCircle(int x, int y, int radius)
{
    int xC = (STAMP_SIZE - 1) / 2;
    int yC = (STAMP_SIZE - 1) / 2;
    double distance = sqrt(
                           pow((x - xC), 2) +
                           pow((y - yC), 2)
                          );
    if (ceil(distance) <= radius)
        return true;
    return false;
}

static bool isInSquare(int x, int y, int halfSide)
{
    int xC = (STAMP_SIZE - 1) / 2;
    int yC = (STAMP_SIZE - 1) / 2;
    if ((abs(x - xC) <= halfSide) &&
        (abs(y - yC) <= halfSide))
        return true;
    return false;
}

static bool isInSlash(int x, int y, int halfLength)
{
    int xC = (STAMP_SIZE - 1) / 2;
    int yC = (STAMP_SIZE - 1) / 2;

    if (((x - xC) == -(y - yC)) &&
        isInCircle(x, y, halfLength))
        return true;
    return false;
}

static bool isInBackslash(int x, int y, int halfLength)
{
    int xC = (STAMP_SIZE - 1) / 2;
    int yC = (STAMP_SIZE - 1) / 2;

    if (((x - xC) == (y - yC)) &&
        isInCircle(x, y, halfLength))
        return true;
    return false;
}

Tool* ToolFactory::createGenericBrush(QColor color,
                                      Figure figure,
                                      Size size)
{
    QImage stamp(STAMP_SIZE, STAMP_SIZE, QImage::Format_ARGB32);

    bool (*isInFigure)(int, int, int);

    switch (figure) {
    case Figure::ROUND:
        isInFigure = isInCircle;
        break;
    case Figure::SQUARE:
        isInFigure = isInSquare;
        break;
    case Figure::SLASH:
        isInFigure = isInSlash;
        break;
    case Figure::BACKSLASH:
        isInFigure = isInBackslash;
        break;
    default:
        break;
    }

    for (int x = 0; x < stamp.width(); x++) {
        for (int y = 0; y < stamp.height(); y++) {

            if (isInFigure(x, y, (int) size)) {
                stamp.setPixel(x, y, color.rgb());
            } else {
                stamp.setPixel(x, y, TRANSPARENT);
            }
        }

    }

    return new GenericBrush(stamp);
}
