#ifndef HEALTH_H
#define HEALTH_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Health
{
private:
    //Imagem
    sf::Sprite sprite;
    sf::Texture texture;

    //variável
    int ammountOfHp;
    void initVariables();
public:
    //Construtor
    Health(const sf::Vector2f& position);
    virtual ~Health();
    //Acessar limites
    const sf::FloatRect getBounds() const;
    //Renderização
    void render(sf::RenderTarget* target);
};

#endif