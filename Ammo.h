#ifndef AMMO_H
#define AMMO_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Ammo
{
private:

    int ammountOfBullets;
    sf::Sprite sprite;
    sf::Texture texture;
    
    void initVariables();
public:
    Ammo(const sf::Vector2f& position);
    virtual ~Ammo();
    const sf::FloatRect getBounds() const;

    void render(sf::RenderTarget* target);
};

#endif