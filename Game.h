#pragma once
#include<map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <cmath>
#include<string>
#include<sstream>

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

	sf::Text gameOverText;

	//Background
	sf::Texture BackgroundTexture;
	sf::Sprite Background;

	//Systems
	unsigned points;
	sf::Music music;
	
	//Player
	Player* player;

	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;


	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;


	

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initBackground();
	void initSystems();
	void initMusic();
	
	void initPlayer();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Functions
	void run();


	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemiesAndCombat();
	void update();
	void renderGUI();
	void renderBackground();
	void render();

};
