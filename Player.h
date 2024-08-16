#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<vector>

enum PLAYER_ANIMATION_STATES{IDLE=0,MOVING_LEFT=1,MOVING_RIGHT=2,MOVING_UP=3,MOVING_DOWN=4};

class Player
{
private:
    sf::Vector2f position;
    sf::FloatRect bounds;

	sf::Sprite sprite;
	sf::Texture texture;
	
	//Animation
	sf::IntRect currentFrame;
	sf::Clock animationTimer;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int ammo;
	int hp;
	int hpMax;

	

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();

public:
	Player();
	virtual ~Player();
	short animationState;
	

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const int& getAmmo() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);
	void gainAmmo(const int value);
	void loseammo(const int value);

	//Functions
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void update();
	void updateAnimations();
	void updateAttack();
	void render(sf::RenderTarget& target);
};