
#include "map.h"

void updateMap(float *groundX1, float *groundX2, float scrollSpeed, float delta, int bgWidth) {
    *groundX1 -= scrollSpeed * delta;
    *groundX2 -= scrollSpeed * delta;

    if (*groundX1 <= -bgWidth) {
        *groundX1 = *groundX2 + bgWidth;
    }
    if (*groundX2 <= -bgWidth) {
        *groundX2 = *groundX1 + bgWidth;
    }
}
