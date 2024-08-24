#ifndef BASE_H
#define BASE_H


#include <SFML/Graphics.hpp>
#include <iostream>

class Base
{
private:
    //Imagem
    sf::Sprite sprite;
    sf::Texture texture;
    //Variáveis
    int hp;
    int hpMax;
    void initVariables();

public:
    //construtor
    Base(const sf::Vector2f& position);
    virtual ~Base();
    //Acessar limites
    const sf::FloatRect getBounds() const;

    //acessar variáveis
    const int& getHp() const;
    const int& getHpMax() const;

    //Funções para modificar varáveis
    void loseHp(int value);
    void gainHp(int value);
    void setHp(int value);

    //Renderização
    void render(sf::RenderTarget* target);
};

#endif