#ifndef GENERICBRUSH_H
#define GENERICBRUSH_H

#include <array>
#include <stdint.h>
#include "tool.h"

#define MAX_STAMP_SIZE 31

typedef std::array <uint32_t, MAX_STAMP_SIZE * MAX_STAMP_SIZE> stampMap;

class GenericBrush : public Tool
{
public:
    GenericBrush(stampMap &stamp);
    void apply(canvasMap& map, uint32_t cursor);

private:
    stampMap m_Stamp;
};

#endif // GENERICBRUSH_H
