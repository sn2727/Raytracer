#include <rt/bbox.h>
#include <core/assert.h>
#include <rt/ray.h>
#include <core/point.h>
#include <algorithm>
#include<tuple>
#include <math.h>


const float maxFloat = std::numeric_limits<float>::max();
const float minFloat = -std::numeric_limits<float>::max();

namespace rt
{

	BBox BBox::empty()
	{
		return BBox();
	}
	BBox BBox::full()
	{
		return BBox(Point(minFloat, minFloat, minFloat), Point(maxFloat, maxFloat, maxFloat));
	}
	void BBox::extend(const Point & point)
	{
		if (this->isEmpty)
		{
			min = point;
			max = point;
		}
		else
		{
			min = rt::min(this->min, point);
			max = rt::max(this->max, point);
		}
		this->isEmpty = false;
	}
	void BBox::extend(const BBox & bbox)
	{
		if (this->isEmpty)
		{
			this->min = bbox.min;
			this->max = bbox.max;
		}
		else
		{
			this->max = rt::max(this->max, bbox.max);
			this->min = rt::min(this->min, bbox.min);
		}
		this->isEmpty = false;
	}
	std::pair< float, float> BBox::intersect(const Ray & ray) const
	{
	Vector invdir(1/ray.d.x, 1/ray.d.y, 1/ray.d.z);
    
    float tmin, tmax, tymin, tymax, tzmin, tzmax; 

    Point bounds[2];
    bounds[0] = min;
    bounds[1] = max;

    int sign[3];
    sign[0] = (invdir.x < 0); 
    sign[1] = (invdir.y < 0); 
    sign[2] = (invdir.z < 0);

    tmin = (bounds[sign[0]].x - ray.o.x) * invdir.x; 
    tmax = (bounds[1-sign[0]].x - ray.o.x) * invdir.x; 
    tymin = (bounds[sign[1]].y - ray.o.y) * invdir.y; 
    tymax = (bounds[1-sign[1]].y - ray.o.y) * invdir.y; 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return std::make_pair(1,0);
    if (tymin > tmin) 
        tmin = tymin; 
    if (tymax < tmax) 
        tmax = tymax; 
 
    tzmin = (bounds[sign[2]].z - ray.o.z) * invdir.z; 
    tzmax = (bounds[1-sign[2]].z - ray.o.z) * invdir.z; 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return std::make_pair(1,0);
    if (tzmin > tmin) 
        tmin = tzmin; 
    if (tzmax < tmax) 
        tmax = tzmax; 

    return std::make_pair(tmin, tmax);
	}


	void BBox::Inflate(float factor)
	{
		float width = max.x - min.x;
		float length = max.y - min.y;
		float height = max.z - min.z;
		Vector inflationVector = Vector(0, 0, 0);
		if (width < length)
		{
			if (width < height)
			{
				inflationVector = Vector(factor, 0, 0);
			}
			else
			{
				inflationVector = Vector(0, 0, factor);
			}
		}
		else
		{
			if (length < height)
			{
				inflationVector = Vector(0, factor, 0);
			}
			else
			{
				inflationVector = Vector(0, 0, factor);
			}
		}
		this->min = this->min - inflationVector;
		this->max = this->max + inflationVector;
	}

	bool BBox::isUnbound()
	{
		if (min.x == minFloat || min.y == minFloat || min.z == minFloat ||
			max.x == maxFloat || max.y == maxFloat || max.z == maxFloat)
			return 1;

		return 0;
	}

	std::pair<int, float> BBox::findGreatestDimensionAndMiddleLocation()
	{
		float xLength = max.x - min.x;
		float yLength = max.y - min.y;
		float zLength = max.z - min.z;
		if (xLength > yLength)
		{
			if (xLength > zLength)
				return std::pair<int, float>(0, xLength / 2 + min.x);

			else
				return std::pair<int, float>(2, zLength / 2 + min.z);
		}

		else
		{
			if (yLength > zLength)
				return std::pair<int, float>(1, yLength / 2 + min.y);
			else
				return std::pair<int, float>(2, zLength / 2 + min.z);
		}

		return std::pair<int, float>();
	}

	float BBox::getSurfaceArea()
	{
		float length = max.x - min.x;
		float width = max.y - min.y;
		float height = max.z - min.z;

		float xyPlaneArea = fabs(length * width);
		float yzPlaneArea = fabs(width * height);
		float zxPlaneArea = fabs(length * height);

		return 2 * (xyPlaneArea + yzPlaneArea + zxPlaneArea);
	}
	float BBox::getXLength()
	{
		if (isEmpty)
			return 0;

		return this->max.x - this->min.x;
	}

	float BBox::getYLength()
	{
		if (isEmpty)
			return 0;

		return this->max.y - this->min.y;
	}

	float BBox::getZLength()
	{
		if (isEmpty)
			return 0;

		return this->max.z - this->min.z;
	}
}
