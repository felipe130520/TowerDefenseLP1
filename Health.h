#ifndef HEALTH_H
#define HEALTH_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Health
{
private:

    int ammountOfHp;
    sf::Sprite sprite;
    sf::Texture texture;
    
    void initVariables();
public:
    Health(const sf::Vector2f& position);
    virtual ~Health();
    const sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget* target);
};

#endif