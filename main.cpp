#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <stdlib.h>  

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
	srand (time(NULL));
	float numberPoints = roundf(RandomFloat(4, 40));

	std::cout << "Generating " << numberPoints << " random points" << std::endl;

	std::vector<Vec2f> points;
	for(int i = 0; i < numberPoints; i++) {
		points.push_back(Vec2f(RandomFloat(0, 800), RandomFloat(0, 600)));
	}
		
	std::cout << "\n ========== " << std::endl;

	Delaunay triangulation;
	std::vector<Triangle> tr = triangulation.triangulate(points);

	// SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Delaunay triangulation");

	// Transform each points of each vector as a rectangle
	std::vector<sf::RectangleShape*> squares;

	for(auto p = begin(points); p != end(points); p++) {
		sf::RectangleShape *c1 = new sf::RectangleShape(sf::Vector2f(4, 4));
		c1->setPosition(p->x, p->y);
		squares.push_back(c1);
	}
	/*
	for(auto t = begin(tr); t != end(tr); t++) {
		sf::RectangleShape *c1 = new sf::RectangleShape(sf::Vector2f(5, 5));
		c1->setPosition(t->p1.x, t->p1.y);
		squares.push_back(c1);
	
		sf::RectangleShape *c2 = new sf::RectangleShape(sf::Vector2f(5, 5));
 		c2->setPosition(t->p2.x, t->p2.y);
		squares.push_back(c2);

		sf::RectangleShape *c3 = new sf::RectangleShape(sf::Vector2f(5, 5));
		c3->setPosition(t->p3.x, t->p3.y);
		squares.push_back(c3);
	}
	*/

	// Remove the doubles
	/*
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
*/
	// Make the lines
	std::vector<std::array<sf::Vertex, 2> > lines;
	for(auto t = begin(tr); t != end(tr); t++) {
		sf::Vector2f p1(t->p1.x + 2, t->p1.y + 2);	
		sf::Vector2f p2(t->p2.x + 2, t->p2.y + 2);	
		sf::Vector2f p3(t->p3.x + 2, t->p3.y + 2);	
		
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
