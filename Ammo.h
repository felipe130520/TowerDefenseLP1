#ifndef AMMO_H
#define AMMO_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Ammo
{
private:
    //Imagem
    sf::Sprite sprite;
    sf::Texture texture;
    //Variáveis
    int ammountOfBullets;
    void initVariables();
public:
    //Construtor
    Ammo(const sf::Vector2f& position);
    virtual ~Ammo();
    //Acessar os limites
    const sf::FloatRect getBounds() const;
    //Renderização
    void render(sf::RenderTarget* target);
};

#endif