#ifndef TOOL_H
#define TOOL_H

//#include "canvas.h"
#include <stdint.h>
#include <vector>

typedef std::vector<uint32_t> canvasMap;

class Tool
{
public:
    virtual void apply(canvasMap& map, uint32_t cursor) = 0;
};

#endif // TOOL_H
