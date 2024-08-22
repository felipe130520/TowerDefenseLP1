#include "Base.h"

void Base::initVariables()
{
    this->hpMax = 100;
    this->hp = this->hpMax;
}

void Base::initShape(const sf::Vector2f& position)
{
    sf::Vector2f baseSize(100.f, 100.f);

    this->shape.setSize(baseSize);
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setPosition(position);
}

Base::Base(const sf::Vector2f& position)
{
    this->initVariables();
    this->initShape(position);
}

Base::~Base()
{

}

const sf::FloatRect Base::getBounds() const
{
    return this->shape.getGlobalBounds();
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

void Base::setHp(int value)
{
    this->hp = value;
}

void Base::update()
{

}

void Base::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}