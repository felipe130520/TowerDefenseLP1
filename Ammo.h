#ifndef AMMO_H
#define AMMO_H

#include <SFML/Graphics.hpp>


class Ammo
{
private:

    int ammountOfBullets;
    sf::RectangleShape shape;
    
    void initVariables();
    void initShape(const sf::Vector2f& position);
public:
    Ammo(const sf::Vector2f& position);
    virtual ~Ammo();
    const sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget* target);
};

#endif