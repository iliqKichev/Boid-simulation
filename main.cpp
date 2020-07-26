#include <SFML/Graphics.hpp>

#include "Boid.hpp"
#include <cmath>
#include <vector>
#include <random>
#include <iostream>

int main()
{
    const unsigned NUMBER_OF_BOIDS = 50;

    sf::Image icon;
    if(!icon.loadFromFile("Boids.png")){
        sf::RenderWindow error(sf::VideoMode(400, 100), "Failed loading resources");
        error.setActive();
        while(error.isOpen()){
            sf::Event event;
            while (error.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    error.close();
            }
        }
        return -1;
    }

    /// Create the main window
    sf::RenderWindow app(sf::VideoMode(1366, 768), "Boid Simulation");
    app.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::View standard = app.getView();
    standard.setCenter(sf::Vector2f(float(app.getSize().x)/2, float(app.getSize().y)/2));

    /// Flock generation
    std::vector<Boid> flock;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> rdPosX(-float(app.getSize().x)/2 + 10, float(app.getSize().x)/2 - 10);
    std::uniform_real_distribution<> rdPosY(-float(app.getSize().y)/2 + 10, float(app.getSize().y)/2 - 10);
    std::uniform_real_distribution<> rdVel(1, 2.5);
    std::uniform_int_distribution<> rdCol(0, NUMBER_OF_BOIDS);
    sf::Color colArr[] = {sf::Color::Red, sf::Color::Green, sf::Color::Cyan, sf::Color::White, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Blue};

    for(int i = 0; i < NUMBER_OF_BOIDS; i ++){
        sf::Vector2f rdPos(rdPosX(gen) + 10, rdPosY(gen) + 10);
        float vel = rdVel(gen);

        float angle = atan2(rdPos.y, rdPos.x) * 57.2957795131;
        sf::Transform trans;
        trans.scale(vel,vel).rotate(angle);

        Boid newBird(rdPos, trans.transformPoint(-200,0));
        newBird.setFillColor(sf::Color(30, 76, 176));
        flock.push_back(newBird);
    }

    sf::Clock clock;

    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        /// Draw everything according to the elapsed time
        /// Using "center-centered" coordinate system
        app.clear();
        app.setView(standard);
        sf::Transform trans;
        trans.translate(sf::Vector2f(standard.getSize().x/2, standard.getSize().y/2));
        trans.scale(sf::Vector2f(1.f,-1.f));

        sf::Vector2f target = sf::Vector2f(sf::Mouse::getPosition(app));
        target = trans.getInverse().transformPoint(target);

        for(auto &bird: flock){
            app.draw(bird, trans);
            bird.fly(flock, clock.getElapsedTime(), target);
        }

        clock.restart();

        app.display();
    }

    return EXIT_SUCCESS;
}
