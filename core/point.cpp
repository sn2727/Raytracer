#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z)
{
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

Point::Point(RGBColor c) {
    this -> x = c.r;
    this -> y = c.g;
    this -> z = c.b;

}

Point::Point(const Float4& f4)
{
    if (fabs(f4[3]) < epsilon) {
        this -> x = 0;
        this -> y = 0;
        this -> z = 0;
    } else {
        this -> x = f4[0]/f4[3];
        this -> y = f4[1]/f4[3];
        this -> z = f4[2]/f4[3];
    }
}

Vector Point::operator - (const Point& b) const {
    return Vector(this -> x - b.x, this -> y - b.y, this -> z - b.z);
}

Point operator+(const Point& a, const Point& b){
    return Point(a.x+b.x, a.y+b.y, a.z+b.z);
}

bool Point::operator == (const Point& b) const {
    return (fabs(this->x - b.x) <= epsilon && fabs(this->y - b.y) <= epsilon 
            && fabs(this->z - b.z)<=epsilon);
}

bool Point::operator != (const Point& b) const {
    return !(fabs(this->x - b.x) <= epsilon && fabs(this->y - b.y) <= epsilon 
            && fabs(this->z - b.z)<=epsilon);
}

Point operator * (float scalar, const Point& b) {
    return Point(scalar * b.x, scalar * b.y, scalar * b.z);
}

Point operator * (const Point& a, float scalar) {
    return Point(scalar * a.x, scalar * a.y, scalar * a.z);
}

Point min(const Point& a, const Point& b) {
    return Point(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point max(const Point& a, const Point& b) {
    return Point(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

}
