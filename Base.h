#ifndef BASE_H
#define BASE_H


#include <SFML/Graphics.hpp>
#include <iostream>

class Base
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int hp;
    int hpMax;
    void initVariables();

public:
    Base(const sf::Vector2f& position);
    virtual ~Base();
    const sf::FloatRect getBounds() const;

    const int& getHp() const;
    const int& getHpMax() const;

    void loseHp(int value);
    void gainHp(int value);
    void setHp(int value);

    void render(sf::RenderTarget* target);
};

#endif