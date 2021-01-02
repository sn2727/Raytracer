#ifndef CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER

#include <rt/cameras/camera.h>

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
    Point mOrigin;
    Vector mBaseX;
    Vector mBaseY;
    Vector mBaseZ;

    virtual Ray getPrimaryRay(float x, float y) const;
};

}


#endif