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
	
	//Funções de inicialização
	void initWindow();

	void initGUI();
	void initBackground();
	void initSystems();
	
	void initBase();
	void initPlayerAndVariables();
public:
	//Construtor e destrutor
	Game();
	virtual ~Game();

	//Função princial
	void run();

	//Funções de atualização
	void togglePausado();
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateCollision();
	void updateBullets();
	void updateEnemieBullets();
	void updateEnemiesAndCombat();
	void updateAmmoCollection();
	void updateHealthCollection();
	void update();
	void updateGameDificulty();

	//Funções de renderização
	void renderGUI();
	void renderBackground();
	void render();

	//Reinciar o jogo
	void restartGame();
};

#endif