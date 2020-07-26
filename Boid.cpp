#include "Boid.hpp"
#include <iostream>
#include <cmath>

Boid::Boid(sf::Vector2f pos, sf::Vector2f vel){
    this->pos = pos;
    this->vel = vel;
    this->acc = sf::Vector2f(0,0);
    this->points[0] = sf::Vector2f(10,0);
    this->points[1] = sf::Vector2f(-5,-5);
    this->points[2] = sf::Vector2f(-5, 5);
    this->setOrigin(0.f,0.f);

    this->scale(sf::Vector2f(2.f,2.f));
    this->move(pos);

    this->VISION_DISTANCE = 20;
    this->VISION_FACTOR = 400;
    this->COHESION_FACTOR = 400;
    this->STEERING_FACTOR = 1000;
    this->ACCELERATION = 1000;

    update();
}

///Drawing stuff
std::size_t Boid::getPointCount() const {
    return 3;
}

sf::Vector2f Boid::getPoint(std::size_t index) const{
    return points[index];
}

sf::Vector2f Boid::vision(std::vector<Boid>& flock){
    sf::Vector2f direction(0,0);

    for(auto bird: flock){
        float distX = bird.pos.x - this->pos.x;
        float distY = bird.pos.y - this->pos.y;

        if(distX*distX + distY*distY < 4*this->VISION_DISTANCE * this->VISION_DISTANCE){
            direction += (bird.pos - this->pos) * float(sqrt(distY * distY + distX * distX) - 2 * this->VISION_DISTANCE);
        }
    }

    if(direction.x * direction.x + direction.y * direction.y){
        direction /= (float)sqrt(direction.x * direction.x + direction.y * direction.y);
    }
    return direction;
}

sf::Vector2f Boid::cohesion(std::vector<Boid>& flock){
    sf::Vector2f direction(0,0);

    for(auto bird: flock){
        float distX = bird.pos.x - this->pos.x;
        float distY = bird.pos.y - this->pos.y;

        if(distX*distX + distY*distY < 4*this->VISION_DISTANCE * this->VISION_DISTANCE){

            direction += (bird.getVel()) * float(sqrt(distY * distY + distX * distX) - 2 * this->VISION_DISTANCE);
        }
    }

    if(direction.x * direction.x + direction.y * direction.y){
        direction /= (float)sqrt(direction.x * direction.x + direction.y * direction.y);
    }
    return direction;
}

sf::Vector2f Boid::steering(sf::Vector2f target){

    sf::Vector2f direction = target - pos;
    if(direction.x * direction.x + direction.y * direction.y){
        direction /= (float)sqrt(direction.x * direction.x + direction.y * direction.y);
    }
    return direction;
}

void Boid::fly(std::vector<Boid>& flock, sf::Time Time, sf::Vector2f target){

    this -> acc = steering(target) * STEERING_FACTOR +
                  vision(flock) * VISION_FACTOR +
                  cohesion(flock) * COHESION_FACTOR;

    float dist = acc.x * acc.x + acc.y * acc.y;
//    if(dist){
//        acc /= float(sqrt(dist));
//    }
//    acc *= ACCELERATION;
    this->vel += this->acc * Time.asSeconds();
    this->pos += this->vel * Time.asSeconds();

    this->setRotation(atan2(vel.y, vel.x) * 57.2957795131);
    this->move(vel * Time.asSeconds());
}

/// Setters and getters
sf::Vector2f Boid::getPos() const {
    return this->pos;
}

void Boid::setPos(const sf::Vector2f pos){
    this->pos = pos;
}

sf::Vector2f Boid::getVel() const {
    return this->vel;
}

void Boid::setAcc(sf::Vector2f acc){
    this -> acc = acc;
}

sf::Vector2f Boid::getAcc() const{
    return this->acc;
}
