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
	std::tuple< float, float, bool> BBox::intersect(const Ray & ray) const
	{
		if ((max - min).lensqr() == 0 || this->isEmpty)
			return std::tuple< float, float, bool>( maxFloat, minFloat, false);

		if (min == Point(minFloat, minFloat, minFloat) && 
			max == Point(maxFloat, maxFloat, maxFloat))
			return std::tuple<float, float, bool>(minFloat, maxFloat, true);

		float minT, maxT;

		float tx0 = (min.x - ray.o.x) / ray.d.x;
		float tx1 = (max.x - ray.o.x) / ray.d.x;

		if (tx0 < tx1)
		{
			minT = tx0;
			maxT = tx1;
		}

		else
		{
			minT = tx1;
			maxT = tx0;
		}

		float ty0 = (min.y - ray.o.y) / ray.d.y;
		float ty1 = (max.y - ray.o.y) / ray.d.y;

		float tyMin = std::min(ty0, ty1);
		float tyMax = std::max(ty0, ty1);

		if ((minT > tyMax) || (tyMin > maxT))
			return std::tuple<float, float, bool>( tyMin, maxT, false);

		if (tyMin > minT)
		{
			minT = tyMin;
		}

		if (tyMax < maxT)
		{
			maxT = tyMax;
		}

		float tz0 = (min.z - ray.o.z) / ray.d.z;
		float tz1 = (max.z - ray.o.z) / ray.d.z;

		float tzMin = std::min(tz0, tz1);
		float tzMax = std::max(tz0, tz1);

		if ((minT > tzMax) || (tzMin > maxT))
			return std::tuple<float, float, bool>(tzMin, maxT, false);

		if (tzMin > minT)
		{
			minT = tzMin;
		}

		if (tzMax < maxT)
		{
			maxT = tzMax;
		}

		if (minT < 0 && maxT < 0)
			return std::tuple<float, float, bool>(minT, maxT, false);

		return std::tuple<float, float, bool>(minT, maxT, true);
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
