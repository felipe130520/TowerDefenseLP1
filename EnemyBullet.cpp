#include "EnemyBullet.h"
#include <cmath>
EnemyBullet::EnemyBullet(sf::Vector2f position, sf::Vector2f playerPos) 
{
    this->movementSpeed = 2.f;
    this->shape.setRadius(6.f);
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setPosition(position);

    this->direction = playerPos - position;

    float magnitude = std::sqrt(this->direction.x * this->direction.x + this->direction.y * this->direction.y);
    if (magnitude != 0) {
        this->direction /= magnitude;
    }   
}

EnemyBullet::~EnemyBullet(){}

const sf::FloatRect EnemyBullet::getBounds() const
{
    return this->shape.getGlobalBounds();
}

void EnemyBullet::update(){

    this->shape.move(this->movementSpeed * this->direction);    
}

void EnemyBullet::render(sf::RenderTarget* target){

    target->draw(this->shape);
}
