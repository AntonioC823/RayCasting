#include "SFML\Graphics.hpp"
#include "Constants.h"
#include "Boundary.h"
#include "Ray.h"
#include <random>

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ray Casting");
	window.setFramerateLimit(FRAME_RATE);

	srand(time(NULL));

	// Creat walls for rays to intersect with
	std::vector<Boundary> walls;

	// Four walls created spanning the borders of the window frame
	// in order to avoid rays checking for a wall that doesn't exist
	walls.push_back(Boundary(0, 0, WINDOW_WIDTH, 0));
	walls.push_back(Boundary(WINDOW_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	walls.push_back(Boundary(WINDOW_WIDTH, WINDOW_HEIGHT, 0, WINDOW_HEIGHT));
	walls.push_back(Boundary(0, WINDOW_HEIGHT, 0, 0));

	// Five random walls created to see ray interactions with different angles walls within the window frame
	int numberOfWalls = 5;
	for (int i = 0; i < numberOfWalls; i++)
	{
		int x1 = rand() % WINDOW_WIDTH, x2 = rand() % WINDOW_WIDTH, y1 = rand() % WINDOW_HEIGHT, y2 = rand() % WINDOW_HEIGHT;

		walls.push_back(Boundary(x1, y1, x2, y2));
	}

	// Create vector of rays with a limit of 360 elemnts
	// DegreeStep used to create rays evenly spaced around the starting point
	std::vector<Ray> rays;
	int possibleNumberOfRays = 360, numberOfRays = 60;
	float degreeStep = possibleNumberOfRays / numberOfRays;
	for (int i = 0; i < possibleNumberOfRays; i += degreeStep)
	{
		rays.push_back(Ray(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, i));
	}

	sf::Mouse mouse;

	while (window.isOpen())
	{
		// Event processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		// Update
		// Rays will always have a starting point at the mouse cursor coordinates
		for (int i = 0; i < rays.size(); i++)
		{
			rays[i].setPosition(mouse.getPosition(window).x, mouse.getPosition(window).y, i * degreeStep);
		}


		// Clear the whole window before rendering a new frame
		window.clear();

		// Draw objects
		for (int i = 0; i < walls.size(); i++)
		{
			window.draw(walls[i].draw());
		}

		// For each ray check intersection with all walls
		// If a ray intersects more than one wall, find the closest wall and stop the ray there
		for (int i = 0; i < rays.size(); i++)
		{
			sf::Vector2f closest(INFINITY, INFINITY);
			float minDistance = INFINITY;
			for (int j = 0; j < walls.size(); j++)
			{
				sf::Vector2f intersection = rays[i].cast(walls[j].getX1(), walls[j].getY1(), walls[j].getX2(), walls[j].getY2());
				if (rays[i].isIntersecting())
				{
					//sf::Vector2f intersection(intersection.x, intersection.y);

					float distance = sqrt(pow(rays[i].getPositionX() - intersection.x, 2) + pow(rays[i].getPositionY() - intersection.y, 2));
					if (distance < minDistance)
					{
						minDistance = distance;
						closest = intersection;
					}
				}
			}

			// Draw each ray from starting point to the closest wall intersection
			sf::VertexArray line(sf::LineStrip, 2);
			line[0].position = sf::Vector2f(rays[i].getPositionX(), rays[i].getPositionY());
			line[1].position = sf::Vector2f(closest.x, closest.y);
			window.draw(line);
		}

		// End the current frame and display its contents on screen
		window.display();
	}

	return 0;
}
