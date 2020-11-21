#ifndef CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle
        );

    Point center;
    Vector forward;
    Vector up;
    Vector sx;
    Vector sy;
    float verticalOpeningAngle;
    float horizontalOpeningAngle;
    float d;

    virtual Ray getPrimaryRay(float x, float y) const;
};

}


#endif