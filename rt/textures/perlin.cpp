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
    float xWeight = coord.x - floor(coord.x);
    float yWeight = coord.y - floor(coord.y);
    float zWeight = coord.z - floor(coord.z);
    RGBColor x0y0z0 = getBlankColor(Point(floor(coord.x), floor(coord.y), floor(coord.z)));
    RGBColor x1y0z0 = getBlankColor(Point(ceil(coord.x), floor(coord.y), floor(coord.z)));
    RGBColor x0y1z0 = getBlankColor(Point(floor(coord.x), ceil(coord.y), floor(coord.z)));
    RGBColor x1y1z0 = getBlankColor(Point(ceil(coord.x), ceil(coord.y), floor(coord.z)));
    RGBColor x0y0z1 = getBlankColor(Point(floor(coord.x), floor(coord.y), ceil(coord.z)));
    RGBColor x1y0z1 = getBlankColor(Point(ceil(coord.x), floor(coord.y), ceil(coord.z)));
    RGBColor x0y1z1 = getBlankColor(Point(floor(coord.x), ceil(coord.y), ceil(coord.z)));
    RGBColor x1y1z1 = getBlankColor(Point(ceil(coord.x), ceil(coord.y), ceil(coord.z)));

    Point value = lerp3d(x0y0z0, x1y0z0, x0y1z0, x1y1z0, 
            x0y0z1, x1y0z1, x0y1z1, x1y1z1, xWeight, yWeight, zWeight);
    //Point value = lerp2d(Point(x0y0z0), Point(x1y0z0), Point(x0y1z0), Point(x1y1z0), xWeight, yWeight);
    //Point value = lerp(Point(x0y0z0), Point(x1y1z0), xWeight);
    //Point value = getBlankColor(coord);
    return RGBColor(value.x, value.y, value.z);
}


rt::RGBColor PerlinTexture::getBlankColor(const Point& coord) {
    float output = 0.f;
    float denom  = 0.f;
    for (int i = 0; i < octaves; i++) {
        output += (amplitude * noise(coord.x * frequency, coord.y * frequency, coord.z * frequency));
        denom += amplitude;
        //frequency *= 2;
        //amplitude *= 1;
    }
    if (fabs(denom) < epsilon) return black;
    return lerp(black, white, output/denom);
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