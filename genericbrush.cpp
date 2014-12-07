#include <math.h>
#include "genericbrush.h"

#define ALPHA_MASK 0x000000FF
#define RED_MASK 0xFF000000
#define GREEN_MASK 0x00FF0000
#define BLUE_MASK 0x0000FF00
#define FACTOR 255

GenericBrush::GenericBrush(stampMap& stamp) :
    m_Stamp(stamp)
{

}

void GenericBrush::apply(canvasMap &map, uint32_t cursor)
{
    int stampCenterIndex = (MAX_STAMP_SIZE * MAX_STAMP_SIZE - 1) / 2;
    int startIndex = cursor - stampCenterIndex;
    int endIndex = cursor + stampCenterIndex;

    for (int i = startIndex, j = 0; i <= endIndex; i++, j++) {

        double stampAlpha = (m_Stamp[j] && ALPHA_MASK) / FACTOR;
        double stampRed = ((m_Stamp[j] && RED_MASK) >> 24) * stampAlpha;
        double stampGreen = ((m_Stamp[j] && GREEN_MASK) >> 16)  * stampAlpha;
        double stampBlue = ((m_Stamp[j] && BLUE_MASK) >> 8) * stampAlpha;

//        double canvasAplha = (map[i] && ALPHA_MASK) / FACTOR;
        double canvasRed = ((map[i] && RED_MASK) >> 24) * (1 - stampAlpha);
        double canvasGreen = ((map[i] && GREEN_MASK) >> 16) * (1 - stampAlpha);
        double canvasBlue = ((map[i] && BLUE_MASK) >> 8) * (1 - stampAlpha);


        map[i] = (int) floor (canvasRed + stampRed) << 24
              | (int) floor (canvasGreen + stampGreen) << 16
              | (int) floor (canvasBlue + stampBlue) << 8;
    }
}
