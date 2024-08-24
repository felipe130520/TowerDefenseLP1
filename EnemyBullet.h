#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include<SFML/Graphics.hpp>
#include <iostream>

class EnemyBullet
{
private:
	//Imagem
	sf::Sprite sprite;
	sf::Texture texture;
	//Variáveis
    sf::Vector2f direction;
	float movementSpeed;

public:
	//Construtor
	EnemyBullet(sf::Vector2f position, sf::Vector2f playerPos);
	virtual ~EnemyBullet();

	//Acesso aos limites
	const sf::FloatRect getBounds() const;
	//Função de atualização
	void update();
	//Renderização
	void render(sf::RenderTarget* target);
};

#endif