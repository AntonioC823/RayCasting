#include "Ray.h"
#include "Constants.h"

Ray::Ray(int x, int y, float angle)
{
	positionX = x;
	positionY = y;
	directionX = positionX + (cos(angle * PI / 180) * 10);
	directionY = positionY + (sin(angle * PI / 180) * 10);
	didIntersect = false;
}

void Ray::setPosition(int x, int y, float angle)
{
	positionX = x;
	positionY = y;

	directionX = positionX + (cos(angle * PI / 180) * 10);
	directionY = positionY + (sin(angle * PI / 180) * 10);
}

// Function used for ray casting
// Check for collision between the rays pointing direction and the walls
sf::Vector2f Ray::cast(int boundaryX1, int boundaryY1, int boundaryX2, int boundaryY2)
{
	int x1 = boundaryX1, y1 = boundaryY1, x2 = boundaryX2, y2 = boundaryY2;
	float x3 = positionX, y3 = positionY, x4 = directionX, y4 = directionY;

	// Formula used to check for intersections between lines
	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den != 0)
	{
		float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

		if (t > 0 && t < 1 && u > 0)
		{
			intersection.x = x1 + t * (x2 - x1);
			intersection.y = y1 + t * (y2 - y1);

			didIntersect = true;
			return intersection;
		}
		else
		{
			didIntersect = false;
			return intersection;
		}
	}

	didIntersect = false;
	return intersection;
}

int Ray::getPositionX() const
{
	return positionX;
}

int Ray::getPositionY() const
{
	return positionY;
}

bool Ray::isIntersecting() const
{
	return didIntersect;
}
