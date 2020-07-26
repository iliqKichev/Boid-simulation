#ifndef BOID_CLASS
#define BOID_CLASS

#include<SFML/Graphics.hpp>
#include<vector>

class Boid : public sf::Shape{
    public:
        Boid(sf::Vector2f pos = sf::Vector2f(0,0), sf::Vector2f vel = sf::Vector2f(0, 1));

        // Movement
        void setAcc(sf::Vector2f acc);

        sf::Vector2f getAcc() const;

        sf::Vector2f getVel() const;

        virtual sf::Vector2f getPoint(std::size_t index) const;

        virtual std::size_t getPointCount() const;

        void setPos(const sf::Vector2f pos);

        sf::Vector2f getPos() const;

        void fly(std::vector<Boid>& flock, sf::Time Time, sf::Vector2f target);

    private:

        sf::Vector2f vision(std::vector<Boid>& flock);

        sf::Vector2f cohesion(std::vector<Boid>& flock);

        sf::Vector2f steering(sf::Vector2f target);

        sf::Vector2f pos, vel, acc, points[3];
        float VISION_DISTANCE, VISION_FACTOR, COHESION_FACTOR, STEERING_FACTOR;
        float ACCELERATION;
};

#endif // BOID_CLASS


