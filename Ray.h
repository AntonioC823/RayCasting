#pragma once
#include "SFML\Graphics.hpp"

class Ray
{
public:
	Ray(int x, int y, float angle);
	void setPosition(int x, int y, float angle);
	sf::Vector2f cast(int boundaryX1, int boundaryY1, int boundaryX2, int boundaryY2);
	int getPositionX() const;
	int getPositionY() const;
	bool isIntersecting() const;
private:
	int positionX;
	int positionY;
	float directionX;
	float directionY;
	sf::Vector2f intersection;
	bool didIntersect;
};
