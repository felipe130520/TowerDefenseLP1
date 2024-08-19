#pragma once

#include<SFML/Graphics.hpp>
#include <iostream>

class EnemyBullet
{
private:

	sf::CircleShape shape;
    sf::Vector2f direction;
	float movementSpeed;

public:

	EnemyBullet(sf::Vector2f position, sf::Vector2f playerPos);
	virtual ~EnemyBullet();

	//Accessor
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);
};
