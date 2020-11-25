#include <rt/cameras/perspective.h>
#include <cmath>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    this -> mOrigin = center;
    this -> mBaseZ = forward.normalize();
    Vector right_axis = cross(mBaseZ, up).normalize();
    Vector up_axis = cross(right_axis, mBaseZ);

    this -> mBaseX = right_axis * std::tan(horizontalOpeningAngle / 2.f);
    this -> mBaseY = up_axis * std::tan(verticalOpeningAngle / 2.f);

}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {

    return Ray(mOrigin, (mBaseZ + mBaseX*x + mBaseY*y).normalize());
}

}
