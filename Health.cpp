#include "Health.h"

void Health::initVariables()
{
    this->ammountOfHp = 5;
}



Health::Health(const sf::Vector2f& position)
{
    this->initVariables();
    if(!this->texture.loadFromFile("Textures/heart.png")){
		std::cout << "ERROR::HEALTH::INITTEXTURE::Could not load texture file"<<std::endl;
	}
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.06f, 0.06f);
    this->sprite.setPosition(position);

}

Health::~Health()
{

}

const sf::FloatRect Health::getBounds() const
{
    return this->sprite.getGlobalBounds();
}



void Health::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}