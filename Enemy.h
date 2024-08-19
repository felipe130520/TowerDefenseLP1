#pragma once
#include "EnemyBullet.h"
#include<SFML/Graphics.hpp>
#include <vector>
class Enemy
{
private:
	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;


	float attackCooldown;
	float attackCooldownMax;

	void initVariables();
	void initShape();
public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Acccessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	sf::Vector2f getPosition() const;
	const bool canAttack();

	//Functions
	void update(const sf::Vector2f& center);
	void updateAttack();
	void render(sf::RenderTarget* target);
};
