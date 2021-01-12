#include <rt/textures/perlin.h>
#include <iostream>
namespace rt {

// returns a value in range -1 to 1
static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
{
    this -> white = white;
    this -> black = black;
    this -> frequency = 1;
    this -> amplitude = 1;
    this -> octaves = 0;
}

rt::RGBColor PerlinTexture::getColor(const Point& coord) {
    
    Point x0y0z0 = Point(floor(coord.x*frequency), floor(coord.y*frequency), floor(coord.z*frequency));
    Point x1y0z0 = Point(ceil(coord.x*frequency), floor(coord.y*frequency), floor(coord.z*frequency));
    Point x0y1z0 = Point(floor(coord.x*frequency), ceil(coord.y*frequency), floor(coord.z*frequency));
    Point x1y1z0 = Point(ceil(coord.x*frequency), ceil(coord.y*frequency), floor(coord.z*frequency));
    Point x0y0z1 = Point(floor(coord.x*frequency), floor(coord.y*frequency), ceil(coord.z*frequency));
    Point x1y0z1 = Point(ceil(coord.x*frequency), floor(coord.y*frequency), ceil(coord.z*frequency));
    Point x0y1z1 = Point(floor(coord.x*frequency), ceil(coord.y*frequency), ceil(coord.z*frequency));
    Point x1y1z1 = Point(ceil(coord.x*frequency), ceil(coord.y*frequency), ceil(coord.z*frequency));
    RGBColor c000 = getBlankColor(x0y0z0.x, x0y0z0.y, x0y0z0.z);
    RGBColor c100 = getBlankColor(x1y0z0.x, x1y0z0.y, x1y0z0.z);
    RGBColor c010 = getBlankColor(x0y1z0.x, x0y1z0.y, x0y1z0.z);
    RGBColor c110 = getBlankColor(x1y1z0.x, x1y1z0.y, x1y1z0.z);
    RGBColor c001 = getBlankColor(x1y1z0.x, x1y1z0.y, x1y1z0.z);
    RGBColor c101 = getBlankColor(x1y0z1.x, x1y0z1.y, x1y0z1.z);
    RGBColor c011 = getBlankColor(x0y1z1.x, x0y1z1.y, x0y1z1.z);
    RGBColor c111 = getBlankColor(x1y1z1.x, x1y1z1.y, x1y1z1.z);

    float xWeight = coord.x*frequency - x0y0z0.x;
    float yWeight = coord.y*frequency - x0y0z0.y;
    float zWeight = coord.z*frequency - x0y0z0.z;

    RGBColor value = lerp3d(c000, c100, c010, c110, c001, c101, c011, c111, xWeight, yWeight, zWeight);
    return value;
}


rt::RGBColor PerlinTexture::getBlankColor(int x, int y, int z) {
    float output = 0.f;
    float denom  = 0.f;
    for (int i = 0; i < octaves; i++) {
        output += (amplitude * noise(x, y, z));
        denom += amplitude;
    }
    if (fabs(denom) < epsilon) return black;
    return lerp(black, white, fabs(output/denom));
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    this -> amplitude += amplitude;
    this -> frequency += frequency;
    this -> octaves++;
}

}