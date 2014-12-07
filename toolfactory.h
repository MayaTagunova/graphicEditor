#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H

#include "genericbrush.h"
#include "sys/types.h"

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define TRANSPARENT 0xFFFFFF00

#define PENCIL_SIZE 1

class ToolFactory
{
public:
    ToolFactory();

    GenericBrush* createPencil(uint32_t color);
    GenericBrush* createRoundBrush(uint32_t color, int size);
    GenericBrush* createSquareBrush(uint32_t color, int size);
    GenericBrush* createSlashBrush(uint32_t color, int size);
    GenericBrush* createBackslashBrush(uint32_t color, int size);
    GenericBrush* createRoundEraser(int size);
    GenericBrush* createSquareEraser(int size);
    GenericBrush* createSlashEraser(int size);
    GenericBrush* createBackslashEraser(int size);

private:
    uint32_t m_Color;
};

#endif // TOOLFACTORY_H
