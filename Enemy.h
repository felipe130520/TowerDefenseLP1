#ifndef ENEMY_H
#define ENEMY_H

#include "EnemyBullet.h"
#include<SFML/Graphics.hpp>
#include <vector>
class Enemy
{
private:
	//Pontos
	unsigned pointCount;
	//Imagem
	sf::Sprite sprite;
	sf::Texture texture;
	//Variáveis do inimigo
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;
	float attackCooldown;
	float attackCooldownMax;
	//Função de inicialização
	void initVariables();
public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Funções de acesso
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	sf::Vector2f getPosition() const;
	const bool canAttack();

	//Funções de atualização
	void update(const sf::Vector2f& center);
	void updateAttack();
	
	//Renderização
	void render(sf::RenderTarget* target);
};

#endif