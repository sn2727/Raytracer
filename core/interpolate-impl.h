#include "interpolate.h"

namespace rt {

template <typename T>
T lerp(const T& px0, const T& px1, float xPoint) {
    return Float4(px0) + xPoint*(Float4(px1) - Float4(px0));
}

template <typename T>
T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {
    return Float4(aWeight*Float4(a) + bWeight*Float4(b) + (1-aWeight-bWeight)*Float4(c));
}

template <typename T>
T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {
    return lerp(lerp(px0y0, px0y1, xWeight), lerp(px1y0, px1y1, xWeight), yWeight);
}

template <typename T>
T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
    const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
    float xPoint, float yPoint, float zPoint)
{
    return lerp(lerp2d(px0y0z0, px0y1z0, px1y0z0, px1y1z0, xPoint, yPoint), 
                  lerp2d(px0y0z1, px1y0z1, px0y1z1, px1y1z1, xPoint, yPoint), zPoint); 
}

}