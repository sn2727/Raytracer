#include <rt/cameras/perspective.h>
#include <cmath>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    this -> center = center;
    this -> forward = forward;
    this -> up = up;
    this -> verticalOpeningAngle = verticalOpeningAngle;
    this -> horizontalOpeningAngle = horizontalOpeningAngle;
    this -> d = 1 / tan(verticalOpeningAngle/2);
    this -> sx = (tan(horizontalOpeningAngle/2) * cross(forward, up)).normalize();
    this -> sy = -1*((tan(verticalOpeningAngle/2) * cross(forward, sx)).normalize());
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {

    Vector direction = (d*forward + sx * x + y * sy).normalize();
    return Ray(center, direction);
}

}
