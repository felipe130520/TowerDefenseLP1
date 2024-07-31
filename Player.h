#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<vector>
class Player
{
private:
    sf::Vector2f position;
    sf::FloatRect bounds;
	
	sf::Sprite sprite;
	sf::Texture texture;
	
	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	//Functions
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void update();
	void updateAttack();
	void render(sf::RenderTarget& target);
};