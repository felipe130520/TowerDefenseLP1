#include "Base.h"

void Base::initVariables()
{
    this->hpMax = 100;
    this->hp = this->hpMax;
}



Base::Base(const sf::Vector2f& position)
{
    this->initVariables();
    if(!this->texture.loadFromFile("Textures/tacoTruck.png")){
		std::cout << "ERROR::BULLET::INITTEXTURE::Could not load texture file"<<std::endl;
	}
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.35f, 0.35f);
    this->sprite.setPosition(position.x - 40.f, position.y - 40.f);
}

Base::~Base()
{

}

const sf::FloatRect Base::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int& Base::getHp() const
{
    return this->hp;
} 

const int& Base::getHpMax() const
{
    return this->hpMax;
}

void Base::loseHp(int value)
{
    this->hp -= value;

    if(this->hp < 0){
        this->hp = 0;
    }
}

void Base::gainHp(int value) {
    
    if(this->hp + value > this->hpMax) {
        this->hp = this->hpMax;
        return;
    }

    this->hp += value;
}

void Base::setHp(int value)
{
    this->hp = value;
}


void Base::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}