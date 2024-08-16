
#include "Player.h"


void Player::initVariables()
{
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;

	

	this->movementSpeed = 4.f;

	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
	
	this->hpMax = 100;
	this->hp = this->hpMax;

	this->ammo = 10;
}

void Player::initTexture()
{
	
	//Load texture from file
	if (!this->texture.loadFromFile("Textures/sprite_sheet.png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file"<<std::endl;
	}
}

void Player::initSprite()
{
	this->currentFrame = sf::IntRect ( 0,0,640,426 ); // Frame atual
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	this->sprite.setTextureRect(this->currentFrame);
	//resize the sprite
	this->sprite.scale(0.1f,0.1f);
}

void Player::initAnimations()	
{
	this->animationTimer.restart();
}


Player::Player()
{

	this->initVariables();
	this-> initTexture();
	this->initSprite();
	this->initAnimations();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

const int& Player::getAmmo() const
{
	return this->ammo;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
}

void Player::gainAmmo(const int value)
{
	this->ammo += value;
}

void Player::loseammo(const int value)
{
	this->ammo -= value;
}


void Player::move(const float dirX, const float dirY)
{

	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {

		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::update()
{
	this->updateAttack();
	this->updateAnimations();
}


void Player::updateAnimations()
{
	if (this->animationState == PLAYER_ANIMATION_STATES::IDLE) {

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {



			this->currentFrame.top = 852.f;
			this->currentFrame.left += 640.f;
			if (this->currentFrame.left >= 3840.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animationState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {



			this->currentFrame.top = 426.f;
			this->currentFrame.left += 640.f;
			if (this->currentFrame.left >= 3840.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animationState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {



			this->currentFrame.top = 0.f;
			this->currentFrame.left += 640.f;
			if (this->currentFrame.left >= 3840.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animationState == PLAYER_ANIMATION_STATES::MOVING_UP)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {



			this->currentFrame.top = 1278.f;
			this->currentFrame.left += 640.f;
			if (this->currentFrame.left >= 3840.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animationState == PLAYER_ANIMATION_STATES::MOVING_DOWN)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {



			this->currentFrame.top = 1704.f;
			this->currentFrame.left += 640.f;
			if (this->currentFrame.left >= 3840.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else {
			this->animationTimer.restart();
	}
}
void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}