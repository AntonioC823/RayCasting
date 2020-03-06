#pragma once
#include "SFML\Graphics.hpp"

class Boundary
{
public:
	Boundary(int x1, int y1, int x2, int y2);
	sf::VertexArray draw() const;
	int getX1() const;
	int getY1() const;
	int getX2() const;
	int getY2() const;
private:
	int x1_;
	int y1_;
	int x2_;
	int y2_;
};
