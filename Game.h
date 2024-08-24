#ifndef GAME_H
#define GAME_H
#include<map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Base.h"
#include "Ammo.h"
#include "EnemyBullet.h"
#include "Health.h"
#include <cmath>
#include<string>
#include<sstream>
#include <iostream>
#include <SFML/Audio.hpp>

class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text ammoText;
	sf::Text playerHpText;
	sf::Text baseHpText;

	sf::Text gameOverText;
	sf::Text YouWinText;
	//Background
	sf::Texture BackgroundTexture;
	sf::Sprite Background;

	//Systems
	unsigned points;
	sf::Music music;
	
	//Base
	Base* base;
	
	//Player
	Player* player;

	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Base GUI
	sf::RectangleShape baseHpBar;
	sf::RectangleShape baseHpBarBack;


	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	std::vector<Ammo*> Ammos;

	std::vector<EnemyBullet*> enemyBullets; 

	std::vector<Health*> healths;

	//Pausar
	bool pausado;
	
	//Aumento de dificuldade
	bool firstDifIncrease;
	bool secondDifIncrease;
	bool thirdDifIncrease;
	
	//Private functions
	void initWindow();

	void initGUI();
	void initBackground();
	void initSystems();
	void initMusic();
	
	void initBase();
	void initPlayer();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Functions
	void run();


	void togglePausado();
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemieBullets();
	void updateEnemiesAndCombat();
	void updateAmmoCollection();
	void updateHealthCollection();
	void update();
	void renderGUI();
	void renderBackground();
	void render();

	void restartGame();
	void updateGameDificulty();

};

#endif