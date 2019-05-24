#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include <random>

#include <SFML/Graphics.hpp>

#include "vector2.h"
#include "triangle.h"
#include "delaunay.h"

int main(int argc, char * argv[])
{
	int numberPoints = 40;
	if (argc>1)
	{
		numberPoints = atoi(argv[1]);
	}

	std::default_random_engine eng(std::random_device{}());
	std::uniform_real_distribution<double> dist_w(0, 800);
	std::uniform_real_distribution<double> dist_h(0, 600);

	std::cout << "Generating " << numberPoints << " random points" << std::endl;

	std::vector<Vector2> points;
	for(int i = 0; i < numberPoints; ++i) {
		points.push_back(Vector2{dist_w(eng), dist_h(eng)});
	}

	Delaunay triangulation;
	const std::vector<Triangle> triangles = triangulation.triangulate(points);
	std::cout << triangles.size() << " triangles generated\n";
	const std::vector<Edge> edges = triangulation.getEdges();

	std::cout << " ========= ";

	std::cout << "\nPoints : " << points.size() << std::endl;
	for(const auto &p : points)
		std::cout << p << std::endl;

	std::cout << "\nTriangles : " << triangles.size() << std::endl;
	for(const auto &t : triangles)
		std::cout << t << std::endl;

	std::cout << "\nEdges : " << edges.size() << std::endl;
	for(const auto &e : edges)
		std::cout << e << std::endl;

	// SFML window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Delaunay triangulation");

	// Transform each points of each vector as a rectangle
	std::vector<sf::RectangleShape*> squares;

	for(const auto p : points) {
		sf::RectangleShape *c1 = new sf::RectangleShape(sf::Vector2f(4, 4));
		c1->setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
		squares.push_back(c1);
	}

	// Make the lines
	std::vector<std::array<sf::Vertex, 2> > lines;
	for(const auto &e : edges) {
		lines.push_back({{
			sf::Vertex(sf::Vector2f(
					static_cast<float>(e.p1.x + 2.),
					static_cast<float>(e.p1.y + 2.))),
			sf::Vertex(sf::Vector2f(
					static_cast<float>(e.p2.x + 2.),
					static_cast<float>(e.p2.y + 2.))),
		}});
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// Draw the squares
		for(const auto &s : squares) {
			window.draw(*s);
		}

		// Draw the lines
		for(const auto &l : lines) {
			window.draw(l.data(), 2, sf::Lines);
		}

		window.display();
	}

	return 0;
}
