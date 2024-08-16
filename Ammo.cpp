#include "Ammo.h"

void Ammo::initVariables()
{
    this->ammountOfBullets = 5;
}

void Ammo::initShape(const sf::Vector2f& position)
{
    sf::Vector2f ammoSize(30.f, 30.f);

    this->shape.setSize(ammoSize);
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setPosition(position);
}

Ammo::Ammo(const sf::Vector2f& position)
{
    this->initVariables();
    this->initShape(position);
}

Ammo::~Ammo()
{

}

const sf::FloatRect Ammo::getBounds() const
{
    return this->shape.getGlobalBounds();
}

void Ammo::update()
{

}

void Ammo::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}