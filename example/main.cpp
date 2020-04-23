#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

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

	std::vector<dt::Vector2<double>> points;
	for(int i = 0; i < numberPoints; ++i) {
		points.push_back(dt::Vector2<double>{dist_w(eng), dist_h(eng)});
	}

	dt::Delaunay<double> triangulation;
	const auto start = std::chrono::high_resolution_clock::now();
	const std::vector<dt::Triangle<double>> triangles = triangulation.triangulate(points);
	const auto end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> diff = end - start;

	std::cout << triangles.size() << " triangles generated in " << diff.count()
			<< "s\n";
	const std::vector<dt::Edge<double>> edges = triangulation.getEdges();

	// SFML window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Delaunay triangulation");
	window.setFramerateLimit(1);

	// Transform each points of each vector as a rectangle
	for(const auto p : points) {
		sf::RectangleShape s{sf::Vector2f(4, 4)};
		s.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
		window.draw(s);
	}

	std::vector<std::array<sf::Vertex, 2> > lines;
	for(const auto &e : edges) {
		const std::array<sf::Vertex, 2> line{{
			sf::Vertex(sf::Vector2f(
					static_cast<float>(e.v->x + 2.),
					static_cast<float>(e.v->y + 2.))),
			sf::Vertex(sf::Vector2f(
					static_cast<float>(e.w->x + 2.),
					static_cast<float>(e.w->y + 2.))),
		}};
		window.draw(line.data(), 2, sf::Lines);
	}

	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}
