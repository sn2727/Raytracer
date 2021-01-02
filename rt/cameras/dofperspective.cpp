#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <cmath>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
{
    this -> mOrigin = center;
    this -> mBaseZ = forward.normalize();
    Vector right_axis = cross(mBaseZ, up).normalize();
    Vector up_axis = cross(right_axis, mBaseZ);

    this -> mBaseX = right_axis * std::tan(horizontalOpeningAngle / 2.f);
    this -> mBaseY = up_axis * std::tan(verticalOpeningAngle / 2.f);
    this -> apertureRadius = apertureRadius;
    this -> focalDistance = focalDistance;
    this -> forward = forward;
    this -> focalPoint = center + focalDistance * forward;
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    Vector r(0.5f - random(), 0.5f - random(), 0.5f - random());
    Point origin = mOrigin + r*apertureRadius;
    //Point focalPoint = origin + focalDistance * forward;
    Vector direction = focalPoint - origin;
    return Ray(mOrigin + r*apertureRadius, direction.normalize());
    
}

}