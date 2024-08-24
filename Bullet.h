#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:
	//imagem
	sf::Sprite shape;
	sf::Texture texture;
	//variaveis
	sf::Vector2f direction;
	float movementSpeed;

public:
	//Construtor
	Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Acesso aos limites
	const sf::FloatRect getBounds() const;
	//atualização
	void update();
	//renderização
	void render(sf::RenderTarget* target);
};

#endif