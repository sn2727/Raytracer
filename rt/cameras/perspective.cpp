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
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    float d = 1 / tan(verticalOpeningAngle/2);
    Vector sx = (tan(horizontalOpeningAngle/2) * cross(forward, up)).normalize();
    Vector sy = (tan(verticalOpeningAngle/2) * cross(forward, sx)).normalize();
    Vector direction = (d*forward + sx * x + y * sy).normalize();
    return Ray(center, direction);
}

}
