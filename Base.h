#pragma once

#include <SFML/Graphics.hpp>


class Base
{
private:
    sf::RectangleShape shape;
    int hp;
    int hpMax;
    void initVariables();
    void initShape(const sf::Vector2f& position);
public:
    Base(const sf::Vector2f& position);
    virtual ~Base();
    const sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget* target);
};

