#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "Space.h"

using namespace std;

int main(int, char**) {
    std::cout << "Hello, world!\n";
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!");
    
    int n = 4;
    int num_points = 4*4*4;
    int stride = 100;
    Matrix points3(num_points, n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            for(int k = 0; k < n; ++k){
                points3(0, i*n*n + j*n + k) = i*stride;
                points3(1, i*n*n + j*n + k) = j*stride;
                points3(2, i*n*n + j*n + k) = k*stride;
            }
        }
    }
    Matrix points2(num_points, 2);

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

        points2 = projector*points3;

        window.clear();
        Point2D::draw(points2, window, 5, sf::Color::Blue);
        window.display();
    }
    std::cout << "done\n";
}
