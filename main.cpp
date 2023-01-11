#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "Space.h"

using namespace std;

int main(int, char**) {
    std::cout << "Hello, world!\n";
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!");
    
    vector<Point3D> points3;
    for(int i = 200; i < 600; i+=100){
        for(int j = 200; j < 600; j+=100){
            for(int k = 0; k < 600; k+=100){
                points3.push_back(Point3D(i, j, k));
            }
        }
    }
    vector<Point2D> points2;

    Point2D center(256, 0);
    double ax = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::sleep(sf::seconds(0.05));
        auto projector = Projector(ax, 3.14/4);
        ax += 0.01;

        points2.clear();
        for(auto& p : points3){
            points2.push_back(center + projector*p);
        }

        window.clear();
        for(auto& v : points2)
            v.draw(window);
        window.display();
    }
    std::cout << "done\n";
}
