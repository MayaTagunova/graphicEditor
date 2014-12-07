#include "toolfactory.h"
#include <math.h>

ToolFactory::ToolFactory()
    : m_Color(BLACK)
{
    //createPencil(m_Color);
}

static bool isInCircle(int index, int maxSize, int radius)
{
    int pointX = index % maxSize;
    int pointY = index / maxSize;
    int centerX = (maxSize - 1) / 2;
    int centerY = (maxSize - 1) / 2;

    double distance = sqrt(
                           pow((pointX - centerX), 2) +
                           pow((pointY - centerY), 2)
                          );
    if (ceil(distance) <= radius)
        return true;
    return false;
}

static bool isInSquare(int index, int maxSize, int halfSide)
{
    int pointX = index % maxSize;
    int pointY = index / maxSize;
    int centerX = (maxSize - 1) / 2;
    int centerY = (maxSize - 1) / 2;

    if ((abs(pointX - centerX) <= halfSide) &&
        (abs(pointY - centerY) <= halfSide))
        return true;
    return false;
}

static bool isInSlash(int index, int maxSize, int halfLength)
{
    int pointX = index % maxSize;
    int pointY = index / maxSize;
    int centerX = (maxSize - 1) / 2;
    int centerY = (maxSize - 1) / 2;

    if (((pointX - centerX) == -(pointY - centerY)) &&
        isInCircle(index, maxSize, halfLength))
        return true;
    return false;
}

static bool isInBackslash(int index, int maxSize, int halfLength)
{
    int pointX = index % maxSize;
    int pointY = index / maxSize;
    int centerX = (maxSize - 1) / 2;
    int centerY = (maxSize - 1) / 2;

    if (((pointX - centerX) == (pointY - centerY)) &&
        isInCircle(index, maxSize, halfLength))
        return true;
    return false;
}

GenericBrush* ToolFactory::createPencil(uint32_t color)
{
    stampMap stamp;

    int size = PENCIL_SIZE;
    for (int index = 0; index < stamp.size(); index++) {
        if (isInCircle(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = color;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}

GenericBrush* ToolFactory::createRoundBrush(uint32_t color, int size)
{
    stampMap stamp;

    for (int index = 0; index < stamp.size(); index++) {
        if (isInCircle(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = color;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}

GenericBrush* ToolFactory::createSquareBrush(uint32_t color, int size)
{
    stampMap stamp;

    for (int index = 0; index < stamp.size(); index++) {
        if (isInSquare(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = color;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}

GenericBrush* ToolFactory::createSlashBrush(uint32_t color, int size)
{
    stampMap stamp;

    for (int index = 0; index < stamp.size(); index++) {
        if (isInSlash(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = color;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}

GenericBrush* ToolFactory::createBackslashBrush(uint32_t color, int size)
{
    stampMap stamp;

    for (int index = 0; index < stamp.size(); index++) {
        if (isInBackslash(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = color;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}

GenericBrush* ToolFactory::createRoundEraser(int size)
{
    stampMap stamp;

    for (int index = 0; index < stamp.size(); index++) {
        if (isInCircle(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = WHITE;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}

GenericBrush* ToolFactory::createSquareEraser(int size)
{
    stampMap stamp;

    for (int index = 0; index < stamp.size(); index++) {
        if (isInSquare(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = WHITE;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}

GenericBrush* ToolFactory::createSlashEraser(int size)
{
    stampMap stamp;

    for (int index = 0; index < stamp.size(); index++) {
        if (isInSlash(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = WHITE;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}

GenericBrush* ToolFactory::createBackslashEraser(int size)
{
    stampMap stamp;

    for (int index = 0; index < stamp.size(); index++) {
        if (isInBackslash(index, MAX_STAMP_SIZE, size)) {
            stamp[index] = WHITE;
        } else {
            stamp[index] = TRANSPARENT;
        }
    }

    return new GenericBrush(stamp);
}
