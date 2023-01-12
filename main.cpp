#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "Space.h"
#include "NBodySystem.h"

using namespace std;

int amain(){
    try{
        Matrix m1 = vector<vector<float>>({
            {7.f, 0.f},
            {0.f, 5.f}
        });
        Matrix m2 = vector<vector<float>>({
            {5.f},
            {5.f}
        });
        Matrix m3 = m1*m2;
        cout << m3.to_string();
    } catch (const runtime_error& err){
        printf("terminating due to error:\n\t%s\n", err.what());
        return 1;
    }
    return 0;
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
    sf::RenderWindow window(sf::VideoMode(512, 512), "physics!");
    
    int n = 4;
    int num_points = 4*4*4;
    int stride = 100;
    // Matrix points3(3, num_points);
    // for(int i = 0; i < n; ++i){
    //     for(int j = 0; j < n; ++j){
    //         for(int k = 0; k < n; ++k){
    //             points3(0, i*n*n + j*n + k) = float(i*stride);
    //             points3(1, i*n*n + j*n + k) = float(j*stride);
    //             points3(2, i*n*n + j*n + k) = float(k*stride);
    //         }
    //     }
    // }
    NBodySystem s;

    Matrix points2(num_points, 2);

    Point2D center(256, 256);
    float ax = 0;
    bool first = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::sleep(sf::seconds(0.05f));
        auto projector = Projector(ax, 3.14f*3/8);
        ax += 0.01f;

        s.step(0.003f);
        points2 = (projector*s.getPositions())*128.f+center;

        window.clear();
        Point2D::draw(points2, window, 2, sf::Color::Blue);
        window.display();
        if(first){
            first = false;
            sf::sleep(sf::seconds(3.f));
        }
    }
    std::cout << "done\n";

    return 0;
}
