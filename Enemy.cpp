#include "Enemy.h"
#include <cmath>

void Enemy::initVariables()
{
	this->pointCount = rand() % 2 + 3; 
	 this->type = 0;
	 this->speed = static_cast<float>(this->pointCount) / 3;
	 this->hpMax=static_cast<int>(this->pointCount);
	 this->hp= this->hpMax;
	 this->damage= this->pointCount;
	 this->points= this->pointCount;
}
void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand()%255 +1, rand()%255 + 1, rand()%255 + 1,255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();

	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}


void Enemy::update(const sf::Vector2f& center)
{
	// Posição atual do inimigo
    sf::Vector2f currentPosition = this->shape.getPosition();
    
    // Calcular a direção para o centro da tela
    sf::Vector2f direction = center - currentPosition;
    
    // Calcular a magnitude da direção
	//VGA sendo aplicado
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    // Normalizar a direção
    if (length != 0) {
        direction /= length;
    }
    
    // Mover o inimigo na direção do centro
    this->shape.move(direction * speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
		
}