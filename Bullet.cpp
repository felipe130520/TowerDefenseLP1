#include "Bullet.h"

//Construtor
Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	if(!this->texture.loadFromFile("Textures/bullet.png")){
		std::cout << "ERROR::BULLET::INITTEXTURE::Could not load texture file"<<std::endl;
	}
	this->shape.setTexture(this->texture);
	this->shape.scale(0.05f, 0.05f);
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;

}

Bullet::~Bullet()
{
}
//retornar limites
const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}
//Movimentação da bala
void Bullet::update()
{
	this->shape.move(this->movementSpeed * this->direction);
}
//Renderização
void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}