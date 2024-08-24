#ifndef PLAYER_H
#define PLAYER_H

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<vector>


class Player
{
private:
	//Variaveis para posição e hitbox
    sf::Vector2f position;
    sf::FloatRect bounds;
	//Imagem
	sf::Sprite sprite;
	sf::Texture texture;
	
	//Variaveis
	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int ammo;
	int hp;
	int hpMax;

	

	//Funções de inicialização
	void initVariables();
	void initTexture();
	void initSprite();
	

public:

	Player(sf::Vector2f center);

	//Funções de acesso (get)
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const int& getAmmo() const;

	//Funções de modificação (set)
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setAmmo(int value);
	void setHp(const int hp);
	void loseHp(const int value);
	void gainAmmo(const int value);
	void loseammo(const int value);

	//Funções de movimentação e ataque
	void move(const float dirX, const float dirY);
	const bool canAttack();

	//Funções de atualização
	void update();
	void updateAttack();

	//Renderização
	void render(sf::RenderTarget& target);
};

#endif