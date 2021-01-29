#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>
 
namespace rt {
 

RGBColor::RGBColor(const Float4& f4)
{
/* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
    return RGBColor(this -> r + c.r, this -> g + c.g, this -> b + c.b);
}

float RGBColor::sum() const{
    return (this->r + this->b + this->b);
}


RGBColor RGBColor::operator - (const RGBColor& c) const {
    return RGBColor(this -> r - c.r, this -> g - c.g, this -> b - c.b);
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
    return RGBColor(this -> r * c.r, this -> g * c.g, this -> b * c.b);
}

bool RGBColor::operator == (const RGBColor& c) const {
    return (fabs(this -> r - c.r) <= epsilon && fabs(this -> g - c.g) <= epsilon 
            && fabs(this -> b - c.b) <= epsilon);
}

bool RGBColor::operator != (const RGBColor& b) const {
    return !(fabs(this -> r - b.r) <= epsilon && fabs(this -> g - b.g) <= epsilon 
            && fabs(this -> b - b.b) <= epsilon);
}

RGBColor RGBColor::clamp() const {
    float r = std::max((float)0, std::min(this -> r, (float)1));
    float g = std::max((float)0, std::min(this -> g, (float)1));
    float b = std::max((float)0, std::min(this -> b, (float)1));

    return RGBColor(r, g, b);
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
    return RGBColor(c.r * scalar, c.g * scalar, c.b * scalar);
}

RGBColor operator * (const RGBColor& c, float scalar) {
    return RGBColor(c.r * scalar, c.g * scalar, c.b * scalar);
}

RGBColor operator / (const RGBColor& c, float scalar) {
    return RGBColor(c.r / scalar, c.g / scalar, c.b / scalar);
}

}
