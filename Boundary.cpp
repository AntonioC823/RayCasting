#include "Boundary.h"

Boundary::Boundary(int x1, int y1, int x2, int y2)
{
	x1_ = x1;
	y1_ = y1;
	x2_ = x2;
	y2_ = y2;
}

sf::VertexArray Boundary::draw() const
{
	sf::VertexArray lines(sf::LineStrip, 2);
	lines[0].position = sf::Vector2f(x1_, y1_);
	lines[1].position = sf::Vector2f(x2_, y2_);

	return lines;
}

int Boundary::getX1() const
{
	return x1_;
}

int Boundary::getY1() const
{
	return y1_;
}

int Boundary::getX2() const
{
	return x2_;
}

int Boundary::getY2() const
{
	return y2_;
}
