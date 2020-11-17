#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

Vector::Vector(float x, float y, float z)
{
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

Vector::Vector(const Float4& f4)
{
    /* TODO */
}

Vector Vector::operator + (const Vector& b) const {
    return Vector(this -> x + b.x, this -> y + b.y, this -> z + b.z);
}

Vector Vector::operator - (const Vector& b) const {
    return Vector(this -> x - b.x, this -> y - b.y, this -> z - b.z);
}

Vector Vector::operator - () const {
    return Vector(this -> x * (-1), this -> y * (-1), this -> z * (-1));
}

Vector Vector::normalize() const {
    float length = this->length();
    assert(length > 0);
    return Vector(this -> x / length, this -> y / length, this -> z / length);
}

Vector operator * (float scalar, const Vector& b) {
    return Vector(b.x * scalar, b.y * scalar, b.z * scalar);
}

Vector operator * (const Vector& a, float scalar) {
    return Vector(a.x * scalar, a.y * scalar, a.z * scalar);
}

Vector operator / (const Vector& a, float scalar) {
    return Vector(a.x / scalar, a.y / scalar, a.z / scalar);
}

Vector cross(const Vector& a, const Vector& b) {
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float dot(const Vector& a, const Vector& b) {
    return b.x * a.x + b.y * a.y + b.z * a.z;
}

float Vector::lensqr() const {
    return this -> x * this -> x + this -> y * this -> y + this -> z * this -> z;
}

float Vector::length() const {
    return sqrt(this -> x * this -> x + this -> y * this -> y + this -> z * this -> z);
}

bool Vector::operator == (const Vector& b) const {
    return (this -> x == b.x && this -> y == b.y && this -> z == b.z);
}

bool Vector::operator != (const Vector& b) const {
    return !(this -> x == b.x && this -> y == b.y && this -> z == b.z);
}

Vector min(const Vector& a, const Vector& b) {
    return Vector(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Vector max(const Vector& a, const Vector& b) {
    return Vector(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Point operator + (const Point& a, const Vector& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator + (const Vector& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator - (const Point& a, const Vector& b) {
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point operator * (const Float4& scale, const Point& p) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
