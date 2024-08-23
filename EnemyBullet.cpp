#include "EnemyBullet.h"
#include <cmath>
EnemyBullet::EnemyBullet(sf::Vector2f position, sf::Vector2f playerPos) 
{
    this->movementSpeed = 2.f;

    if(!this->texture.loadFromFile("Textures/enemyBullet.png")) {
        std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file"<<std::endl;
    }

    this->sprite.setTexture(this->texture);
    
    this->sprite.setPosition(position.x + 25.f, position.y + 25.f);

    this->direction = playerPos - position;

    this->sprite.setScale(0.05f, 0.05f);

    float magnitude = std::sqrt(this->direction.x * this->direction.x + this->direction.y * this->direction.y);
    if (magnitude != 0) {
        this->direction /= magnitude;
    }   
}

EnemyBullet::~EnemyBullet(){}

const sf::FloatRect EnemyBullet::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

void EnemyBullet::update(){

    this->sprite.move(this->movementSpeed * this->direction);    
}

void EnemyBullet::render(sf::RenderTarget* target){

    target->draw(this->sprite);
}
