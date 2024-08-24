#include "Player.h"

//Iniciar variáveis do player
void Player::initVariables()
{
	this->movementSpeed = 4.f;

	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
	
	this->hpMax = 100;
	this->hp = this->hpMax;

	this->setAmmo(10);
}

//iniciar a textura
void Player::initTexture()
{
	//Load texture from file
	if (!this->texture.loadFromFile("Textures/cranio.png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file"<<std::endl;
	}
}

//iniciar sprite
void Player::initSprite()
{
	this->sprite.setTexture(this->texture);

	//redimensionar a sprite
	this->sprite.scale(0.1f,0.1f);
}


//Função construtora
Player::Player(sf::Vector2f center)
{
	this->initVariables();
	this-> initTexture();
	this->initSprite();
	this->setPosition(center);
}
//Retornar posição
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}
//Retornar limites
const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
//Retornar hp
const int& Player::getHp() const
{
	return this->hp;
}
//Retornar hp maáximo
const int& Player::getHpMax() const
{
	return this->hpMax;
}
//retornar quantidade de balas
const int& Player::getAmmo() const
{
	return this->ammo;
}
//Definiar posição do player
void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}
//Definiar posição do player
void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}
//Definir quantidade de balas
void Player::setAmmo(int value){
	this->ammo = value;
}
//Definir hp
void Player::setHp(const int hp)
{
	this->hp = hp;
}
//Perder hp
void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
}
//Ganhar munição
void Player::gainAmmo(const int value)
{
	this->ammo += value;
}
//Perder munição
void Player::loseammo(const int value)
{
	this->ammo -= value;
}
//Movimentação
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}
//Retornar se pode atacar (atirar)
const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {

		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}
//Atualizar
void Player::update()
{
	this->updateAttack();

}

//Atualizar ataque
void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}
//Renderizar
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}