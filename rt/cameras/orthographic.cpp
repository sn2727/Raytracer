#include <rt/cameras/orthographic.h>
#include <rt/ray.h>
#include <core/vector.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
    this -> center = center;
    this -> forward = forward.normalize();
    this -> up = up;
    this -> scaleX = scaleX;
    this -> scaleY = scaleY;
    this -> uVec = cross(forward,up).normalize();
    this -> vVec = cross(uVec, forward).normalize();
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    
    Point origin = center + (scaleX * 0.5f * x * uVec) + (scaleY * 0.5f * y * vVec);
    return Ray(origin, forward);
}

}
