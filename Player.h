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

	int hp;
	int hpMax;

	

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
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//Functions
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void update();
	void updateAttack();
	void render(sf::RenderTarget& target);
};