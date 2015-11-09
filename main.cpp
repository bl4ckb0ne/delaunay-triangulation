#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h> 

#include <SFML/Graphics.hpp>

#include "vector2.h"
#include "triangle.h"
#include "delaunay.h"

typedef Vector2<float> Vec2f;

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int main()
{
	float numberPoints = roundf(RandomFloat(4, 40));

	std::vector<Vec2f> points;
	for(int i = 0; i < numberPoints; i++) {
		points.push_back(Vec2f(RandomFloat(0, 130), RandomFloat(0, 100)));
	}
	
	std::vector<Triangle> tr = Delaunay::triangulate(points);

	std::cout << tr.size() << " triangles" << std::endl;
	for(auto i = tr.begin(); i != tr.end(); i++) {
		std::cout << *i << std::endl;
	}

	// SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Delaunay triangulation");
	sf::View scale;
	scale.reset(sf::FloatRect(0, 0, 800/6, 600/6));

	// Transform each points of each vector as a rectangle
	std::vector<sf::RectangleShape*> squares;
	for(auto t = begin(tr); t != end(tr); t++) {
		sf::RectangleShape *c1 = new sf::RectangleShape(sf::Vector2f(2, 2));
		c1->setPosition(t->getP1().getX(), t->getP1().getY());
		squares.push_back(c1);
	
		sf::RectangleShape *c2 = new sf::RectangleShape(sf::Vector2f(2, 2));
 		c2->setPosition(t->getP2().getX(), t->getP2().getY());
		squares.push_back(c2);

		sf::RectangleShape *c3 = new sf::RectangleShape(sf::Vector2f(2, 2));
		c3->setPosition(t->getP3().getX(), t->getP3().getY());
		squares.push_back(c3);
	}

	// Remove the doubles
	for(auto i = begin(squares); i != end(squares); i++) {
		for(auto j = begin(squares); j != end(squares);) {
			if(i != j) {
				if((*i)->getPosition().x == (*j)->getPosition().x && (*i)->getPosition().y == (*j)->getPosition().y) {
					j = squares.erase(j);
				}
				else {
					j++;
				}
			}
			else {
				j++;
			}
		}		
	}

	// Make the lines
	std::vector<std::array<sf::Vertex, 2> > lines;
	for(auto t = begin(tr); t != end(tr); t++) {
		sf::Vector2f p1(t->getP1().getX() + 1, t->getP1().getY() + 1);	
		sf::Vector2f p2(t->getP2().getX() + 1, t->getP2().getY() + 1);	
		sf::Vector2f p3(t->getP3().getX() + 1, t->getP3().getY() + 1);	
		
		lines.push_back({sf::Vertex(p1), sf::Vertex(p2)});	
		
		lines.push_back({sf::Vertex(p2), sf::Vertex(p3)});	
		
		lines.push_back({sf::Vertex(p3), sf::Vertex(p1)});	
	}
 
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		// Comment this line for the resolution
		window.setView(scale);

        window.clear();

		// Draw the squares
		for(auto s = begin(squares); s != end(squares); s++) {
			window.draw(**s);
		}

		// Draw the lines
		for(auto l = begin(lines); l != end(lines); l++) {
			window.draw((*l).data(), 2, sf::Lines);
		}
       	
		window.display();
    }

	return 0;
}
