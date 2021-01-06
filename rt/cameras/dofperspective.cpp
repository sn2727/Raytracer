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
    this -> normal = cross(mBaseX, mBaseY).normalize();
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    Vector perspectiveDir = (mBaseZ + mBaseX*x + mBaseY*y).normalize();
    Point focalPoint = mOrigin + focalDistance*perspectiveDir;
    Point randOrigin = Disc(mOrigin, normal, apertureRadius, nullptr, nullptr).sample().point;
    Vector dir = (focalPoint - randOrigin).normalize();
    return Ray(randOrigin, dir);
}

}