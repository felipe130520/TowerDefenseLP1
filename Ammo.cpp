#include "Ammo.h"

void Ammo::initVariables()
{
    this->ammountOfBullets = 5;
}



Ammo::Ammo(const sf::Vector2f& position)
{
    this->initVariables();
    if(!this->texture.loadFromFile("Textures/ammoTaco.png")){
		std::cout << "ERROR::AMMO::INITTEXTURE::Could not load texture file"<<std::endl;
	}
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.08f, 0.08f);
    this->sprite.setPosition(position);

}

Ammo::~Ammo()
{

}

const sf::FloatRect Ammo::getBounds() const
{
    return this->sprite.getGlobalBounds();
}



void Ammo::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}